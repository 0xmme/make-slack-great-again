// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include <QHash>
#include <QList>
#include <QObject>
#include <QSize>
#include <QString>

class QNetworkReply;

namespace net {

// One search hit: a small animated preview to paint in the picker grid, and the
// full-size URL that actually gets posted to the conversation.
struct GifResult {
    QString previewUrl;  // small animated GIF, sized for a grid cell
    QString postUrl;     // what goes into the message (unfurls to an animation)
    QSize   previewSize; // intrinsic preview dimensions — drives the masonry layout
    QString description; // title / alt text, used as the cell's accessible name
};

// GIPHY GIF search (https://developers.giphy.com/docs/api).
//
// Google shut the Tenor API down on 2026-06-30, so GIPHY is the provider here —
// the same move WhatsApp and Signal made. Everything provider-specific is behind
// this one class: swapping in another catalogue means reimplementing search()
// and parseResponse(), not touching the picker.
//
// One search at a time: a new query aborts the in-flight reply, because the
// picker re-queries as the user types and only the newest answer is wanted.
// Results arrive on `results` tagged with the query they belong to, so a caller
// can drop a straggler that lost the race.
//
// Answers are cached per query for the life of the object. A free GIPHY key is
// capped at 100 calls an hour, which a search-as-you-type box would otherwise
// burn through in a single sitting — backspacing to a query already fetched
// re-renders from the cache and costs nothing.
//
// The API needs a key. It is resolved per call in this order:
//   1. the user's key from SecretStore ("gif/giphy/apiKey"), set in Settings
//   2. AppCredentials::giphyKey, baked in at build time via credentials.cmake
// With neither, search() fails immediately with a configuration message rather
// than issuing a keyless request GIPHY would reject anyway.
class GifSearch : public QObject {
    Q_OBJECT
public:
    explicit GifSearch(QObject *parent = nullptr);
    ~GifSearch() override;

    // Effective key (user override first, then the build-time default).
    static QString apiKey();
    // Persist the user's key; an empty value clears it and falls back to the
    // build-time default. Stored through SecretStore, never plaintext QSettings.
    static void    setUserApiKey(const QString &key);
    // The user's key on its own, with no build-time fallback (for the settings
    // field, which must show an empty box when only a baked-in key exists).
    static QString userApiKey();
    static bool    configured() { return !apiKey().isEmpty(); }
    // Where to send a user who needs to create a key.
    static QString apiKeyUrl();
    // Attribution mark. GIPHY's API terms require apps to "conspicuously
    // display" it wherever the API is used, so the picker always shows it.
    static QString attributionText();

    // Run a search; an empty query fetches the trending set, which is what the
    // picker shows before anything is typed. A cached query re-emits `results`
    // on the next event-loop turn without touching the network.
    void search(const QString &query, int limit = kDefaultLimit);
    // Drop the in-flight request and stop caring about its answer.
    void cancel();
    // Forget cached answers (e.g. after the API key changes).
    void clearCache();

    // Map a GIPHY search/trending body to results. Entries missing a usable
    // rendition are skipped rather than emitted half-filled. Exposed so the
    // wire format can be tested without a network round trip.
    static QList<GifResult> parseResponse(const QByteArray &body);

    // The request URL for a query, with the key applied. Exposed for tests.
    static QString requestUrl(const QString &query, int limit, const QString &key);

    // User-facing text for a failed request. `httpStatus` is 0 when the request
    // never reached GIPHY. Deliberately built from the status alone: Qt's
    // QNetworkReply::errorString() embeds the full request URL, and ours
    // carries api_key= in its query string — see the note at the call site.
    // Exposed so the no-secrets-in-the-message property can be tested.
    static QString errorMessage(int httpStatus);

    // GIPHY beta keys allow 50 per call; 30 fills the panel without waste.
    static constexpr int kDefaultLimit = 30;

signals:
    void results(const QString &query, const QList<net::GifResult> &gifs);
    // keyRejected marks the failures a new key would fix (missing key, or one
    // GIPHY refused), so the picker can offer the setup form again instead of
    // leaving the user on an error with nothing to act on.
    void failed(const QString &query, const QString &error, bool keyRejected);

private:
    void onReply(QNetworkReply *reply, const QString &query);

    QNetworkReply                   *_inflight = nullptr;
    QHash<QString, QList<GifResult>> _cache; // normalised query → answer
};

} // namespace net
