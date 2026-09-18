// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

class QWidget;

// Configure the native frame while Qt paints the unified header underneath it.
void configureMacTitleBar(QWidget *window);

// Apply the user's "Double-click a window's title bar to" system preference
// (Zoom / Minimize / Fill / Do nothing) to the window.
void performMacTitleBarDoubleClick(QWidget *window);
