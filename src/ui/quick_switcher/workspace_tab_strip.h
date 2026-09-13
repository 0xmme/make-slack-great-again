// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include <QPixmap>
#include <QString>
#include <QWidget>
#include <vector>

class ImageCache;
class PopupTooltip;

// One row of workspace bubbles — the same bubbles as the sidebar rail, at the
// same size — with the current workspace's name beside them. Selection is an
// accent ring *around* the bubble in a reserved margin every bubble has, so
// picking one never resizes or shifts anything. The quick switcher's
// "which workspace am I searching" control: click a bubble or use ←/→ (the
// dialog forwards the keys) to move the current one. Bubbles can be marked
// dimmed (no match for the query) so the eye lands on the workspaces that
// still have something to offer.
class WorkspaceTabStrip : public QWidget {
    Q_OBJECT
public:
    struct Entry {
        QString teamId;
        QString name;
        QString iconUrl;
    };

    explicit WorkspaceTabStrip(ImageCache *imgCache, QWidget *parent = nullptr);

    void setWorkspaces(std::vector<Entry> entries);
    int  count() const { return static_cast<int>(_entries.size()); }

    int     currentIndex() const { return _current; }
    QString currentTeamId() const;
    // Clamped; a change emits currentChanged. No-op on an empty strip.
    void    setCurrentIndex(int index);
    // Move by `delta` wrapping at both ends.
    void    step(int delta);

    // Per-index "has results" flags; an empty vector clears the dimming.
    void setDimmed(std::vector<bool> dimmed);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override { return sizeHint(); }

signals:
    void currentChanged(int index);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void leaveEvent(QEvent *) override;

private:
    struct EntryPrivate {
        Entry   info;
        QPixmap icon;
    };
    QRect bubbleRect(int i) const;
    int   hitTest(const QPoint &pos) const;
    void  loadIcons();
    void  setHovered(int i);

    std::vector<EntryPrivate> _entries;
    std::vector<bool>         _dimmed;
    int                       _current  = -1;
    int                       _hovered  = -1;
    ImageCache               *_imgCache = nullptr;
    PopupTooltip             *_tooltip  = nullptr;

    static constexpr int kBubble  = 40; // rail size
    static constexpr int kRadius  = 10;
    static constexpr int kRing    = 2; // selection ring width
    static constexpr int kRingGap = 2; // clear gap between bubble and ring
    static constexpr int kSlot    = kBubble + 2 * (kRing + kRingGap);
};
