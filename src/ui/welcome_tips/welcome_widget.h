// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once
#include <QWidget>
#include <QList>

class QLabel;
class QFrame;
class QVBoxLayout;

class WelcomeWidget : public QWidget {
    Q_OBJECT
public:
    explicit WelcomeWidget(QWidget *parent = nullptr);

    // Rebuild the shortcut rows from the registry — the send/newline bindings
    // change with the "send with Ctrl+Enter" option.
    void refreshShortcuts();

protected:
    void resizeEvent(QResizeEvent *e) override;
    void showEvent(QShowEvent *e) override;

private:
    void applyTheme();
    void repositionContent();
    void buildRows();

    QWidget         *_content = nullptr;
    QVBoxLayout     *_vbox    = nullptr; // rows are appended to it by buildRows()
    QLabel          *_title   = nullptr;
    QFrame          *_rule    = nullptr;
    QList<QLabel *>  _chipLabels;
    QList<QLabel *>  _plusLabels;
    QList<QLabel *>  _actionLabels;
    // One widget per shortcut row, in registry order — repositionContent() hides
    // trailing ones when the panel is taller than the space it has.
    QList<QWidget *> _rows;
};
