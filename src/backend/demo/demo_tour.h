// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
// Scripted walkthrough of the demo workspace (`--demo-tour demo/tour.json`),
// recorded by scripts/demo-video.sh. The tour drives the real widgets: it moves
// the real pointer (the capture draws it), sends genuine mouse/key events to
// whatever window is under it — context menus and pickers are popups — and
// calls the same private entry points the UI does. No screen coordinates in
// the script. Compiled only with MSGA_DEMO (Debug builds).
#pragma once

#include "backend/demo/demo_tour_script.h"

#include <QObject>
#include <QPoint>
#include <QPointer>
#include <QString>
#include <functional>
#include <optional>

class ContextMenu;
class MainWindow;
class QWidget;

namespace demo {

class Tour : public QObject {
public:
    Tour(MainWindow *window, TourScript script, QObject *parent = nullptr);

    // Waits for the first conversation to be on screen, prints "tour: start"
    // (the recording script trims to it), then runs the steps; "tour: end" and
    // QCoreApplication::quit() follow the Quit step or the end of the list.
    void start();

private:
    using Done = std::function<void()>;

    void runNext();
    void run(const TourStep &step, Done done);

    // Primitives — every one ends by calling `done` from the event loop.
    // Positions are global (screen) coordinates.
    void moveCursor(QPoint global, Done done);
    void click(QPoint global, Done done, Qt::MouseButton button = Qt::LeftButton);
    void typeText(const QString &text, double cps, Done done);
    void pressKey(int key, const QString &text, Done done);
    void after(int ms, Done done);
    void parkCursor(Done done); // neutral spot over the messages

    void         dispatchMouse(QPoint global, bool press, Qt::MouseButton button);
    void         dispatchHover(QPoint global);
    QWidget     *widgetAt(QPoint global) const;
    ContextMenu *visibleMenu() const;
    QPoint       menuItemPoint(const QString &label) const; // null when absent

    std::optional<QString> findMessageTs(const QString &fragment) const;
    QPoint                 messagePoint(const QString &ts, int dxFromLeft, int dyFromTop) const;
    // Global centre of hover-toolbar button `btn` (0 react, 1 forward, 2 more) of
    // the row showing `ts`; the row must be hovered for the list to act on it.
    QPoint                 toolbarButtonPoint(const QString &ts, int btn) const;
    QPoint                 conversationPoint(const QString &convId) const;
    QPoint                 centerOf(const QWidget *w) const;
    void                   finish();

    MainWindow       *_win;
    TourScript        _script;
    size_t            _index = 0;
    QPointF           _pos;     // where the pointer is (global)
    QPointer<QWidget> _hovered; // last widget that got Enter, for the matching Leave (menus die)
    bool              _done = false;
};

} // namespace demo
