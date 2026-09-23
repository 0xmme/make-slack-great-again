// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include "user_avatar.h"

#include <QWidget>
#include <QPixmap>
#include <QPainter>

#include <vector>

// Displays a user avatar (28×28 rounded rect) with a presence/DND indicator dot,
// or — for a group DM — a Slack-style stack of up to three overlapping member
// avatars followed by the member count (setGroup).
// No Q_OBJECT — state is updated externally via setPixmap/setPresence/setDnd/clearAvatar.
class HeaderAvatarWidget : public QWidget {
public:
    struct GroupMember {
        QString url;     // avatar URL; the pixmap arrives via setGroupPixmap
        QString initial; // placeholder letter until (or instead of) the photo
        QPixmap pixmap;
    };

    explicit HeaderAvatarWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(kSingleBox, kSingleBox);
    }
    void setPixmap(const QPixmap &px) {
        _pixmap = px;
        update();
    }
    void setPresence(bool active) {
        _state.isActive = active;
        update();
    }
    void setDnd(bool dnd) {
        _state.dndEnabled = dnd;
        update();
    }
    void setPhantomAway(bool phantom) {
        _state.phantomAway = phantom;
        update();
    }
    // Apps/bots can't go offline — suppress the (meaningless) presence dot.
    void setShowPresence(bool show) {
        _state.showPresence = show;
        update();
    }
    void clearAvatar() {
        _pixmap = {};
        _state  = {};
        _displayName.clear(); // else the placeholder shows the last DM's initial
        _group.clear();
        _groupCount = 0;
        setFixedSize(kSingleBox, kSingleBox);
        update();
    }
    // Group mode: `members` (at most kMaxStack are shown) stacked left to right,
    // then `count` (the group's size) as text. An empty list leaves single mode.
    void setGroup(std::vector<GroupMember> members, int count) {
        if (members.size() > kMaxStack)
            members.resize(kMaxStack);
        _group      = std::move(members);
        _groupCount = count;
        setFixedSize(groupWidth(), kSingleBox);
        update();
    }
    void setGroupPixmap(const QString &url, const QPixmap &px) {
        for (auto &m : _group)
            if (m.url == url)
                m.pixmap = px;
        update();
    }
    const std::vector<GroupMember> &group() const { return _group; }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter p(this);
        if (!_group.empty()) {
            paintGroup(p);
            return;
        }
        const QString initial = _displayName.isEmpty() ? QString{} : _displayName.left(1);
        const int     offset  = (width() - 28) / 2;
        UserAvatar::paint(
            p,
            QRect(offset, offset, 28, 28),
            _pixmap,
            initial,
            _state,
            /*cornerRadius=*/4,
            devicePixelRatioF(),
            /*borderColor=*/Qt::white
        );
    }

public:
    // Optional: set display name so the placeholder initial letter is correct.
    void setDisplayName(const QString &name) {
        _displayName = name;
        update();
    }

private:
    static constexpr int         kSingleBox = 36;
    static constexpr int         kStackSize = 24; // one stacked avatar
    static constexpr int         kStackStep = 16; // left edge to left edge
    static constexpr int         kRing      = 2;  // separating ring around each
    static constexpr int         kCountGap  = 6;
    static constexpr std::size_t kMaxStack  = 3;

    QString countText() const { return _groupCount > 0 ? QString::number(_groupCount) : QString{}; }
    QFont   countFont() const {
        QFont f = font();
        f.setBold(true);
        return f;
    }
    int groupWidth() const {
        const int     n      = int(_group.size());
        const int     stackW = kRing * 2 + kStackSize + (n - 1) * kStackStep;
        const QString t      = countText();
        return stackW +
               (t.isEmpty() ? 0 : kCountGap + QFontMetrics(countFont()).horizontalAdvance(t));
    }
    void paintGroup(QPainter &p) {
        p.setRenderHint(QPainter::Antialiasing);
        const int y = (height() - kStackSize) / 2;
        // Later avatars overlap earlier ones; each sits on a ring of the header
        // surface so the overlap reads as separate chips.
        for (int i = 0; i < int(_group.size()); ++i) {
            const auto &m = _group[i];
            const QRect r(kRing + i * kStackStep, y, kStackSize, kStackSize);
            p.setPen(Qt::NoPen);
            p.setBrush(Th::c().surface.content);
            p.drawRoundedRect(r.adjusted(-kRing, -kRing, kRing, kRing), 4 + kRing, 4 + kRing);
            if (!m.pixmap.isNull())
                UserAvatar::paintPhoto(p, r, m.pixmap, devicePixelRatioF(), 4);
            else
                UserAvatar::paintInitial(
                    p, r, m.initial, Th::c().presence.away, Qt::white, 4, kStackSize * 0.38
                );
        }
        const QString t = countText();
        if (t.isEmpty())
            return;
        const int x = kRing * 2 + kStackSize + (int(_group.size()) - 1) * kStackStep + kCountGap;
        p.setFont(countFont());
        p.setPen(Th::c().text.secondary);
        p.drawText(QRect(x, 0, width() - x, height()), Qt::AlignLeft | Qt::AlignVCenter, t);
    }

    QPixmap                  _pixmap;
    UserAvatar::State        _state;
    QString                  _displayName;
    std::vector<GroupMember> _group;
    int                      _groupCount = 0;
};
