// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "workspace_tab_strip.h"
#include "ui/image_cache.h"
#include "ui/popup_tooltip/popup_tooltip.h"
#include "ui/theme.h"
#include "ui/theme_manager.h"
#include "ui/workspace_switcher/workspace_bubble.h"

#include <QFontMetrics>
#include <QMouseEvent>
#include <QPainter>

WorkspaceTabStrip::WorkspaceTabStrip(ImageCache *imgCache, QWidget *parent)
    : QWidget(parent), _imgCache(imgCache) {
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _tooltip = new PopupTooltip(this);
    if (_imgCache) {
        connect(_imgCache, &ImageCache::loaded, this, [this](const QString &url) {
            bool any = false;
            for (auto &ep : _entries) {
                if (ep.info.iconUrl != url || !ep.icon.isNull())
                    continue;
                const QPixmap px = _imgCache->get(url);
                if (px.isNull())
                    continue;
                ep.icon = Ui::scaleWorkspaceIcon(px, kBubble, devicePixelRatioF());
                any     = true;
            }
            if (any)
                update();
        });
    }
    connect(&ThemeManager::instance(), &ThemeManager::themeChanged, this, [this] { update(); });
}

void WorkspaceTabStrip::setWorkspaces(std::vector<Entry> entries) {
    _entries.clear();
    _entries.reserve(entries.size());
    for (auto &e : entries)
        _entries.push_back({.info = std::move(e)});
    _dimmed.clear();
    _hovered = -1;
    _current = _entries.empty() ? -1 : 0;
    loadIcons();
    updateGeometry();
    update();
}

void WorkspaceTabStrip::loadIcons() {
    if (!_imgCache)
        return;
    for (auto &ep : _entries) {
        if (ep.info.iconUrl.isEmpty() || !ep.icon.isNull())
            continue;
        const QPixmap px = _imgCache->get(ep.info.iconUrl);
        if (!px.isNull())
            ep.icon = Ui::scaleWorkspaceIcon(px, kBubble, devicePixelRatioF());
        // null → in flight; the loaded() hook above fills it in.
    }
}

QString WorkspaceTabStrip::currentTeamId() const {
    return (_current >= 0 && _current < count()) ? _entries[_current].info.teamId : QString();
}

void WorkspaceTabStrip::setCurrentIndex(int index) {
    if (_entries.empty())
        return;
    index = std::clamp(index, 0, count() - 1);
    if (index == _current)
        return;
    _current = index;
    update();
    emit currentChanged(_current);
}

void WorkspaceTabStrip::step(int delta) {
    if (_entries.empty())
        return;
    const int n = count();
    setCurrentIndex(((_current + delta) % n + n) % n);
}

void WorkspaceTabStrip::setDimmed(std::vector<bool> dimmed) {
    _dimmed = std::move(dimmed);
    update();
}

QSize WorkspaceTabStrip::sizeHint() const {
    return {0, kSlot};
}

QRect WorkspaceTabStrip::bubbleRect(int i) const {
    // Every slot reserves the ring margin, selected or not — the bubble itself
    // sits at a fixed size and place.
    const int gap = Th::c().spacing.sm;
    return {i * (kSlot + gap) + kRing + kRingGap, kRing + kRingGap, kBubble, kBubble};
}

int WorkspaceTabStrip::hitTest(const QPoint &pos) const {
    for (int i = 0; i < count(); ++i)
        if (bubbleRect(i).contains(pos))
            return i;
    return -1;
}

void WorkspaceTabStrip::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    const auto &th = Th::c();

    for (int i = 0; i < count(); ++i) {
        const auto  &ep  = _entries[i];
        const QRectF r   = QRectF(bubbleRect(i));
        const bool   dim = i < static_cast<int>(_dimmed.size()) && _dimmed[i] && i != _current;
        p.setOpacity(dim ? 0.35 : 1.0);
        // Plain bubble: the rail's active/hover treatment (a white ring inside
        // the bubble, a lighter fill) erodes the edge on a light card and reads
        // as the icon shrinking — selection is painted around it instead.
        Ui::paintWorkspaceBubble(
            p,
            r,
            {.teamId = ep.info.teamId, .name = ep.info.name, .icon = ep.icon, .radius = kRadius},
            font()
        );
        p.setOpacity(1.0);
        if (i == _current || i == _hovered) {
            const qreal  half = kRing / 2.0;
            const qreal  out  = kRingGap + half;
            const QColor c    = i == _current ? th.accent.def : th.divider.strong;
            p.setPen(QPen(c, kRing));
            p.setBrush(Qt::NoBrush);
            p.drawRoundedRect(r.adjusted(-out, -out, out, out), kRadius + out, kRadius + out);
        }
    }

    // The current workspace's name, so the letter bubbles don't have to be
    // decoded — right of the last bubble, elided to the room left.
    if (_current >= 0 && _current < count()) {
        const int x = bubbleRect(count() - 1).right() + 1 + kRing + kRingGap + th.spacing.md;
        QFont     f = font();
        f.setPixelSize(th.fonts.lg);
        f.setBold(true);
        p.setFont(f);
        p.setPen(th.text.primary);
        const QRect   r(x, 0, width() - x, kSlot);
        const QString name =
            QFontMetrics(f).elidedText(_entries[_current].info.name, Qt::ElideRight, r.width());
        p.drawText(r, Qt::AlignVCenter | Qt::AlignLeft, name);
    }
}

void WorkspaceTabStrip::mousePressEvent(QMouseEvent *e) {
    if (e->button() != Qt::LeftButton)
        return;
    const int i = hitTest(e->pos());
    if (i >= 0)
        setCurrentIndex(i);
}

void WorkspaceTabStrip::setHovered(int i) {
    if (i == _hovered)
        return;
    _hovered = i;
    if (i >= 0) {
        const QRect r = bubbleRect(i);
        _tooltip->showAbove(_entries[i].info.name, QRect(mapToGlobal(r.topLeft()), r.size()));
    } else {
        _tooltip->hide();
    }
    update();
}

void WorkspaceTabStrip::mouseMoveEvent(QMouseEvent *e) {
    setHovered(hitTest(e->pos()));
}

void WorkspaceTabStrip::leaveEvent(QEvent *) {
    setHovered(-1);
}
