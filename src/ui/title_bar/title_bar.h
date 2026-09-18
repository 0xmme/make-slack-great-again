// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once
#include <QWidget>

class QLabel;
class QPushButton;
class QStackedLayout;
class PopupTooltip;

// Unified header on macOS, custom controls for the frameless window elsewhere.
// Handles drag-to-move (startSystemMove), double-click maximize/restore,
// and window state changes (updates the max/restore button icon).
class TitleBar : public QWidget {
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);

    void setTitle(const QString &title);
    void setContent(QWidget *content);

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void showEvent(QShowEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;
    bool eventFilter(QObject *watched, QEvent *e) override;

private:
    void applyTheme();
    void updateMaxButton();
    void togglePin();
    void updatePinButton();
    void refreshHoverState();

    QLabel         *_titleLabel        = nullptr;
    QStackedLayout *_contentLayout     = nullptr;
    QPushButton    *_minBtn            = nullptr;
    QPushButton    *_maxBtn            = nullptr;
    QPushButton    *_closeBtn          = nullptr;
    QPushButton    *_pinBtn            = nullptr;
    PopupTooltip   *_tooltip           = nullptr;
    bool            _pinned            = false;
    bool            _dragging          = false; // manual drag (non-Wayland)
    bool            _systemMovePending = false; // startSystemMove() in flight (Wayland)
    bool            _windowConnected   = false;
    QPoint          _dragOffset;
};
