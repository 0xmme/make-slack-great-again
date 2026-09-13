// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include <QColor>
#include <QFont>
#include <QPixmap>
#include <QRectF>
#include <QString>

class QPainter;

// The workspace bubble — a rounded square holding the workspace icon, or a
// letter on a colour derived from the team id — as painted by the sidebar
// rail (WorkspaceSwitcher). Shared so the quick switcher's workspace tabs are
// the same bubbles the user already knows, not a second rendering that drifts.
namespace Ui {

// Stable per-workspace hue: the same team is the same colour everywhere.
QColor workspaceBubbleColor(const QString &teamId);

struct WorkspaceBubble {
    QString teamId;
    QString name; // letter fallback when `icon` is null
    QPixmap icon; // already scaled to the bubble's physical size (may be null)
    bool    active  = false;
    bool    hovered = false;
    qreal   radius  = 10.0; // corner radius in logical px
};

// Paints the bubble into `r` (which sets the bubble size — the letter scales
// with it). The caller owns render hints and any badge on top.
void paintWorkspaceBubble(
    QPainter &p, const QRectF &r, const WorkspaceBubble &b, const QFont &base
);

// `src` scaled to a square `sizePx` bubble at `dpr`, ready for paintWorkspaceBubble.
QPixmap scaleWorkspaceIcon(const QPixmap &src, int sizePx, qreal dpr);

} // namespace Ui
