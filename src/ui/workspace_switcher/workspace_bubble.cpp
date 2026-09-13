// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "workspace_bubble.h"
#include "ui/theme.h"

#include <QPainter>
#include <QPainterPath>

namespace Ui {

// Reference bubble: the rail's 40 px square with a 17 px letter. Other sizes
// scale the glyph proportionally so a 28 px tab still reads as the same mark.
static constexpr int kRefBubble = 40;
static constexpr int kRefLetter = 17;

QColor workspaceBubbleColor(const QString &teamId) {
    const int hue = static_cast<int>((qHash(teamId) * 37u) % 360u);
    return QColor::fromHsl(hue, Th::c().workspaceHslSaturation, Th::c().workspaceHslLightness);
}

void paintWorkspaceBubble(
    QPainter &p, const QRectF &r, const WorkspaceBubble &b, const QFont &base
) {
    QColor bg = workspaceBubbleColor(b.teamId);
    if (b.active)
        bg = bg.lighter(125);
    else if (b.hovered)
        bg = bg.lighter(115);
    p.setBrush(bg);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(r, b.radius, b.radius);

    if (!b.icon.isNull()) {
        QPainterPath clip;
        clip.addRoundedRect(r, b.radius, b.radius);
        p.setClipPath(clip);
        p.drawPixmap(r, b.icon, QRectF(b.icon.rect()));
        p.setClipping(false);
    } else {
        // Letter fallback. White on the saturated bubble colour is the one
        // intentional literal here (same as the rail's ring below).
        const QChar ch = b.name.isEmpty() ? QChar('?') : b.name.at(0).toUpper();
        p.setPen(Qt::white);
        QFont f = base;
        f.setPixelSize(qMax(8, qRound(r.height() * kRefLetter / kRefBubble)));
        f.setBold(true);
        p.setFont(f);
        p.drawText(r, Qt::AlignCenter, QString(ch));
    }

    // White ring for active / hover
    if (b.active || b.hovered) {
        p.setPen(QPen(QColor(255, 255, 255, b.active ? 200 : 100), b.active ? 2.0 : 1.5));
        p.setBrush(Qt::NoBrush);
        const qreal inset = 0.75;
        p.drawRoundedRect(
            r.adjusted(inset, inset, -inset, -inset), b.radius - inset, b.radius - inset
        );
    }
}

QPixmap scaleWorkspaceIcon(const QPixmap &src, int sizePx, qreal dpr) {
    const int phys = qRound(sizePx * dpr);
    QPixmap   px   = src.scaled(phys, phys, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    px.setDevicePixelRatio(dpr);
    return px;
}

} // namespace Ui
