// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include <QWidget>

// The "Message sent · Undo" chip the composer floats above its box for a few
// seconds after each send. Like PopupTooltip it is an in-window child overlay
// (reparented onto the top-level window, never a Qt::ToolTip/popup top-level),
// so it lands where it is computed on Wayland and can overlap the message list
// without pushing it around. The whole chip is the button: clicking anywhere
// on it emits undoClicked().
class UndoSendPill : public QWidget {
    Q_OBJECT
public:
    explicit UndoSendPill(QWidget *parent = nullptr);

    // Reveal (or re-place) the chip right-aligned above `anchorGlobalRect`.
    void showAbove(const QRect &anchorGlobalRect);

signals:
    void undoClicked();

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void enterEvent(QEnterEvent *e) override;
    void leaveEvent(QEvent *e) override;
    // Repaint the host region we vacated (translucent child overlays leave
    // stale pixels in the backing store on some platforms).
    void hideEvent(QHideEvent *e) override;

private:
    QSize   chipSize() const;
    // The translated pieces, computed per call so a locale switch shows.
    QString sentText() const;
    QString undoText() const;
    QString hintText() const;

    bool _hover = false;

    static constexpr int kPadH   = 12;
    static constexpr int kPadV   = 7;
    static constexpr int kGapDot = 8; // around the "·" separator
    static constexpr int kRadius = 8;
    static constexpr int kShadow = 6; // transparent padding around the body
    static constexpr int kGap    = 6; // gap between chip and anchor top
};
