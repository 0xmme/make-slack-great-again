// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include <cstdint>
#include <functional>
#include <QHash>
#include <QImage>
#include <QList>
#include <QObject>
#include <QPixmap>
#include <QQueue>
#include <QSize>

class QMovie;
class QNetworkAccessManager;

// Shared cache for public-URL image downloads: avatars, attachment previews, favicons.
// Deduplicates concurrent requests for the same URL via an in-flight sentinel.
// Emits loaded(url) when a download completes so callers can refresh their views.
//
// For auth-required Slack file downloads use Session::downloadFile() instead.
class ImageCache : public QObject {
    Q_OBJECT
public:
    explicit ImageCache(QObject *parent = nullptr);

    // Returns the cached pixmap for url (null QPixmap while loading or on error).
    // First call for a given url triggers a download; subsequent calls while the
    // download is in-flight return null immediately and wait for the loaded() signal.
    QPixmap get(const QString &url);

    // Intrinsic (unscaled) pixel size of url's image, or an invalid QSize while
    // it is unknown. Starts a download on first call exactly like get(), so a
    // caller that only needs geometry never has to ask for the pixels.
    //
    // Layout MUST use this rather than get().size(): rebuildLayout() measures
    // every row in the conversation, so sizing through get() required the
    // decoded pixmap of every image in the channel to be resident at once.
    // Past the memory cap that turned into an eviction treadmill — each pass
    // evicted the entry the next pass asked for first, so every layout re-read
    // and re-decoded the whole image cache (~21 MB/s of PNG decoding on a
    // preview-heavy channel). Sizes are a few bytes and never evicted, and are
    // read from the image header without decoding where the format allows.
    QSize sizeOf(const QString &url);

    // Player for an animated image (GIF / animated WebP), or nullptr when the
    // url hasn't loaded yet or decodes to a single frame. The QMovie is created
    // lazily, shared between callers and owned by the cache — callers connect
    // to frameChanged() and drive start()/setPaused() by visibility.
    // Each non-null return is an acquire: the entry is pinned against eviction
    // until the caller hands it back with releaseMovie(). A caller that stores
    // the pointer must release it exactly once when done (and drop the pointer).
    QMovie *movie(const QString &url);

    // Release one movie() acquisition. When the last holder releases, the
    // QMovie (and its decoded frames) is deleted and the entry becomes a
    // normal LRU citizen again — re-acquiring later recreates the player
    // from the retained bytes (or a fresh download if evicted meanwhile).
    void releaseMovie(const QString &url);

    // True when bytes decode to a multi-frame animation.
    static bool isAnimatedImage(const QByteArray &bytes);

    // Animation playback is a user setting (Settings → Appearance → Visual
    // effects), and the point of turning it off is to spend neither RAM nor
    // CPU on it. The cache's share is the retained encoded bytes of every
    // animated download — a Giphy GIF is megabytes — so:
    //
    // setAnimationsRetained(false) stops keeping them at all (every animated
    // image is then a still first frame; movie() answers nullptr) and drops the
    // bytes already held by entries no one is playing. Switching back on
    // forgets those stills so the next get() re-fetches (from the disk cache)
    // and the animation comes back. Pass the OR of the per-kind toggles.
    //
    // discardAnimation(url) is the per-kind form for callers that know what
    // kind of image a url is (a custom emoji vs. in-message media — the cache
    // can't tell): it drops one entry's animation bytes when no one holds its
    // player. restoreDiscardedAnimations() forgets every discarded still (a
    // kind was re-enabled) so they re-fetch as animations.
    void setAnimationsRetained(bool on);
    bool animationsRetained() const { return _retainAnimations; }
    void discardAnimation(const QString &url);
    void restoreDiscardedAnimations();

    // Longest side a decoded pixmap may have. Inline images are painted into at
    // most ~400×300 logical px, yet a 4000×3000 unfurl or file preview decoded
    // at native size is 48 MB of pixels for an 800×600 preview — a handful of
    // those fill every cache cap in the app and were the bulk of the
    // multi-hundred-MB footprints in issue #64. The bound is the widest inline
    // image at the sharpest attached screen (kMaxDecodeLogical × DPR, at least
    // 2×), so 2× displays lose nothing and any one entry stays ≤ ~2 MB at 2×.
    // Computed once on first use. The full-size image viewer fetches its own
    // high-resolution copy and is unaffected.
    static constexpr int kMaxDecodeLogical = 400;
    static int           maxDecodeDim();

    // Decode image bytes so the longest side is at most maxDim (aspect kept,
    // never upscaled); maxDim <= 0 means maxDecodeDim(). Raster formats decode
    // scaled; SVG renders at up to 256 px. Null on undecodable bytes. The
    // QImage form is safe on a worker thread (QPixmap is GUI-thread only).
    static QPixmap decodeBounded(const QByteArray &bytes, int maxDim = 0);
    static QImage  decodeBoundedImage(const QByteArray &bytes, int maxDim = 0);

    // Decode synchronously inside get()/fetch completion instead of on a pool
    // thread. For tests that assert on state right after get(); production
    // decodes asynchronously so a big JPEG never stalls a paint.
    void setSynchronousDecode(bool on) { _syncDecode = on; }

    // The size decodeBounded() yields for an image of intrinsic size `sz` —
    // lets header-only measurement (sizeOf) agree with the decoded pixmap.
    static QSize boundedSize(QSize sz, int maxDim = 0);

    // Wire a persistent backing store: load is called before any network fetch;
    // save is called after each successful download so the bytes survive restarts.
    // Passing empty functions disables the backing store.
    void setDiskCache(
        std::function<QByteArray(const QString &)>               load,
        std::function<void(const QString &, const QByteArray &)> save
    );

    // Soft ceiling on the decoded pixels + animation bytes held in RAM. The map
    // used to grow unbounded for the whole process lifetime — every avatar,
    // preview and GIF ever scrolled past stayed resident. Once over the cap the
    // least-recently-used entries are dropped (see evictIfNeeded for what is
    // pinned). Default below; the setter exists for tests.
    // 32 MB: with decodeBounded() capping one entry at ~2 MB this still holds
    // every avatar/emoji in view plus a screenful of previews; the previous
    // 64 MB, stacked on the two message lists' own caps, was most of the
    // 300 MB+ footprints reported in issue #64.
    static constexpr qint64 kDefaultMemoryCap = 32LL * 1024 * 1024;
    void                    setMemoryCap(qint64 bytes) { _memoryCap = bytes; }
    [[nodiscard]] qint64    memoryBytes() const { return _memBytes; }

signals:
    void loaded(const QString &url);

private:
    struct Entry {
        QPixmap    pixmap;                     // first frame for animated images
        QByteArray animatedBytes;              // raw bytes, kept only for multi-frame images
        QMovie    *movie            = nullptr; // lazily created from animatedBytes
        int        movieRefs        = 0;       // movie() acquisitions not yet released
        bool       inFlight         = false;
        // The bytes were an animation but were not kept (retention off, or
        // discardAnimation): the pixmap is a still that must be re-fetched
        // once animations are wanted again.
        bool       animationDropped = false;
        qint64     cost             = 0; // last accounted bytes (pixmap + animatedBytes)
        quint64    lastUsed         = 0; // _useTick at the last get()/account(); eviction order
    };

    // Issue the network fetch for url and install the in-flight sentinel.
    // Shared by get() and sizeOf() so both enter the cache the same way. Only
    // kMaxParallelFetches downloads run at once; the rest wait in _fetchQueue.
    void startFetch(const QString &url);
    void issueFetch(const QString &url);
    void pumpFetchQueue();
    // Decode bytes (from disk or network) for url off the GUI thread, then
    // install the result via finishDecode() and emit loaded().
    void decodeAsync(const QString &url, QByteArray bytes, bool saveToDisk);
    void finishDecode(const QString &url, const QByteArray &bytes, QImage img, bool saveToDisk);

    // A scroll through an image-heavy channel used to fire every unfurl and
    // avatar download at once (HTTP/2 multiplexes without limit). Each reply
    // body is a multi-MB buffer and each completion decodes through tens of MB
    // of scratch, so dozens were live simultaneously — and macOS's allocator
    // keeps freed large blocks resident at that high-water mark for the rest of
    // the session (issue #64). Bounding parallelism bounds the peak.
    static constexpr int kMaxParallelFetches = 4;

    // Record url's intrinsic size once known (idempotent).
    void noteSize(const QString &url, const QSize &sz);

    // True while url is on the do-not-fetch list: bytes that arrived but could
    // not be decoded (permanent — they are not an image), or a transport error
    // still inside its retry cooldown.
    [[nodiscard]] bool isFailed(const QString &url) const;
    // permanent=false applies kErrorCooldownMs before another attempt is allowed.
    void               markFailed(const QString &url, bool permanent);

    // Recompute url's memory cost, mark it most-recently-used, then evict down
    // to the cap. Call after any change to an entry's pixmap/animatedBytes.
    void account(const QString &url);
    // Drop LRU entries until under the cap, skipping pinned ones (in-flight, or
    // backing a live QMovie that callers may still hold a pointer to).
    void evictIfNeeded(const QString &protectUrl);

    // Wait this long before retrying a url that failed with a transport error.
    static constexpr qint64 kErrorCooldownMs = 60'000;

    QHash<QString, Entry>  _cache;
    // Monotonic use counter: every get() hit and account() stamps the entry, so
    // eviction (rare, O(n) scan) drops the least recently *used* entry rather
    // than the least recently inserted one — hot avatars used to be evicted and
    // re-decoded on every cap pass because hits never touched the old list.
    quint64                _useTick = 0;
    // Intrinsic sizes, and urls not to re-fetch. Both are keyed by url and hold
    // no pixels, so they are deliberately exempt from the memory cap and from
    // eviction: forgetting them is what produced repeated decodes and repeated
    // downloads of the same failing url on every layout pass.
    QHash<QString, QSize>  _sizes;
    QHash<QString, qint64> _failedUntil; // value 0 == never retry
    qint64                 _memBytes  = 0;
    qint64                 _memoryCap = kDefaultMemoryCap;
    QNetworkAccessManager *_nam;
    QQueue<QString>        _fetchQueue; // urls waiting for a fetch slot
    int                    _activeFetches    = 0;
    bool                   _syncDecode       = false;
    bool                   _retainAnimations = true;

    std::function<QByteArray(const QString &)>               _diskLoad;
    std::function<void(const QString &, const QByteArray &)> _diskSave;
};
