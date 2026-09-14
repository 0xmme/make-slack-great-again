// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include "network/gif_search.h"
#include "ui/virtual_list/virtual_list_widget.h"

#include <QFrame>
#include <QHash>
#include <QList>
#include <QRect>
#include <QSet>
#include <QString>
#include <QTimer>

class QLabel;
class QStackedLayout;
class QMovie;
class ImageCache;
class StyledLineEdit;

// Two-column masonry of animated GIF previews — zero-widget and custom-painted,
// the same approach as EmojiGrid and the message list.
//
// GIFs have wildly different aspect ratios, so a fixed cell grid would letterbox
// almost everything; each cell instead keeps its source aspect and the shorter
// column takes the next result, which is the layout every GIF picker uses.
//
// Only previews inside (or just outside) the viewport are animated: playback is
// resynced after every paint, so scrolling a result away pauses its QMovie
// instead of leaving thirty decoders running behind a 460px panel.
class GifGrid : public VirtualListWidget {
    Q_OBJECT
public:
    explicit GifGrid(QWidget *parent = nullptr);
    ~GifGrid() override;

    // Shared in-memory (disk-backed) cache the previews are fetched through.
    void setImageCache(ImageCache *cache);

    // Replace the displayed results and relayout. Releases the movies held for
    // the previous set, so callers can swap result pages freely.
    void setResults(const QList<net::GifResult> &results);
    void clear();

    bool isEmpty() const { return _items.isEmpty(); }
    int  contentHeight() const { return _contentH; }

    int  selected() const { return _sel; }
    void setSelected(int idx);
    void moveSelection(int dCol, int dRow);
    void activateSelected();

signals:
    void gifActivated(const net::GifResult &gif);

protected:
    void doPaint(QPaintEvent *event) override;
    void doMousePress(QMouseEvent *event) override;
    void doMouseMove(QMouseEvent *event) override;
    void doMouseRelease(QMouseEvent *event) override;
    void doMouseLeave() override;
    void scrollContentsBy(int dx, int dy) override;
    void resizeEvent(QResizeEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private:
    struct Item {
        net::GifResult gif;
        QRect          rect; // content coords (scroll not applied)
        int            col;
    };

    void relayout();
    void updateScrollRange();
    void ensureVisible(int idx);
    int  itemAt(const QPoint &vp) const;

    // Acquire (and animate) the movie for a visible preview; pause and hand back
    // the ones that scrolled away. Called at the end of every paint.
    void syncPlayback(const QSet<QString> &visibleUrls);
    // Hand every held movie back to the cache. Safe to call repeatedly.
    void releaseAllMovies();

    static constexpr int kCols   = 2;
    static constexpr int kGap    = 6;   // gutter between cells
    static constexpr int kMargin = 6;   // grid edge margin
    static constexpr int kMinH   = 60;  // floor for a very wide GIF
    static constexpr int kMaxH   = 200; // ceiling for a very tall one
    static constexpr int kRadius = 6;

    ImageCache              *_imgCache = nullptr;
    QList<Item>              _items;
    QHash<QString, QMovie *> _movies; // url → movie we hold an acquisition on
    int                      _contentH = 0;
    int                      _sel      = -1;
    int                      _hover    = -1;
};

// Floating GIF picker popup — mounted once per composer, opened on demand.
// Auto-dismisses on outside click (Qt::Popup), like the emoji picker.
//
// Typing re-queries GIPHY after a debounce; an empty field shows the trending
// set.
//
// With no API key the panel turns into a setup form — explain, link out to a
// free key, take it inline — rather than an empty grid or a dead end. The
// composer button stays visible either way: hiding it would make GIF search
// undiscoverable, and a prebuilt binary carries no baked-in key, so for most
// users the hidden button would never appear at all. Taking the key here rather
// than sending the user to Settings also keeps this working identically in all
// four composers, including the one inside the modal forward dialog.
class GifPickerPopup : public QFrame {
    Q_OBJECT
public:
    explicit GifPickerPopup(QWidget *parent = nullptr);

    // Shared image cache for the previews — forwarded to the grid.
    void setImageCache(ImageCache *cache);

    // Show the picker at globalPos and focus the search field.
    void open(const QPoint &globalPos);

signals:
    // Emitted when the user picks a GIF; url is the full-size one to post.
    void gifSelected(const QString &url);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    // What the body area is showing; the grid is only visible in Results.
    enum class State { NeedsKey, Loading, Results, Empty, Error };

    void     applyTheme();
    void     setState(State state, const QString &message = {});
    void     requery();       // fire the search for the current field text
    void     scheduleQuery(); // debounce a keystroke into a requery
    // The NeedsKey page: explainer, a link to GIPHY's dashboard, and a field
    // that saves the key and drops straight into results.
    QWidget *buildSetupPage();
    void     saveKeyFromSetup();
    // Height the setup form needs at the panel's width.
    int      compactHeight() const;
    // Size the panel for the current state: full for the grid, compact for the
    // setup form. Keeps the bottom edge on the anchor (re-showing if visible).
    void     fitHeight();
    // Move so the bottom edge sits on the anchor, clamped onto the screen.
    void     place();

    // Deliberately long for a search box: a free GIPHY key allows 100 calls an
    // hour, so the debounce is what keeps a typed phrase to one request rather
    // than one per letter. GifSearch caches on top of this.
    static constexpr int kDebounceMs = 450;

    StyledLineEdit *_search           = nullptr;
    QStackedLayout *_body             = nullptr; // grid / message / setup
    GifGrid        *_grid             = nullptr;
    QLabel         *_message          = nullptr; // Loading / Empty / Error
    QWidget        *_setup            = nullptr; // NeedsKey
    StyledLineEdit *_keyEdit          = nullptr; // key field on the setup page
    QLabel         *_setupText        = nullptr;
    QLabel         *_setupError       = nullptr;
    QLabel         *_attribution      = nullptr; // footer, shown with the grid/message
    QLabel         *_setupAttribution = nullptr; // same mark, in the setup page's Save row
    net::GifSearch *_api              = nullptr;
    QTimer          _debounce;
    QString         _pending; // query the in-flight request belongs to
    State           _state        = State::Loading;
    int             _anchorX      = 0; // where open() was asked to put the panel:
    int             _anchorBottom = 0; // left edge, and the bottom edge to grow up from
};
