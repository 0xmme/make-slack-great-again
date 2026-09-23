// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include "backend/domain.h"

#include <QWidget>

class CanvasPage;
class IconButton;
class PopupTooltip;
class QLabel;
class Session;

// Full-window in-app viewer for a canvas shared as a message file (huddle
// notes, canvases posted into a chat) — what opens when its preview card is
// clicked, like the official client's canvas panel. Hosts its own CanvasPage,
// so the canvas is readable AND editable exactly like a channel canvas tab,
// with a small header bar (open in browser / close) above it. Mounted once per
// top-level window and reused via open(), like TableViewerOverlay; Esc, the
// close button or a backdrop click dismisses it (flushing pending edits).
class CanvasViewerOverlay : public QWidget {
    Q_OBJECT
public:
    explicit CanvasViewerOverlay(QWidget *windowParent);

    void open(Session *session, const ConversationId &conv, const File &canvas);
    void dismiss();

protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    bool eventFilter(QObject *obj, QEvent *ev) override;

private:
    void  applyTheme();
    void  relayout();
    QRect panelRect() const;

    static constexpr int kMargin    = 40;   // backdrop visible around the panel
    static constexpr int kMaxPanelW = 1120; // CanvasPage column + its side padding

    QWidget      *_panel    = nullptr;
    QLabel       *_heading  = nullptr;
    IconButton   *_openBtn  = nullptr;
    IconButton   *_closeBtn = nullptr;
    CanvasPage   *_page     = nullptr;
    PopupTooltip *_tip      = nullptr;
    QString       _permalink;
};
