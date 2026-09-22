// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
// The tour script (demo/tour.json) as data: verbs the demo::Tour performs, and
// the parser — Widgets-free so tests can cover it without a MainWindow.
#pragma once

#include <QByteArray>
#include <QSize>
#include <QString>
#include <QStringList>
#include <optional>
#include <vector>

namespace demo {

struct TourStep {
    enum class Kind {
        Wait,        // ms
        Open,        // arg = conversation id — click its sidebar row
        Scroll,      // num = pixels (negative = up) in the message list
        Hover,       // arg = message text fragment — park the pointer on it
        Thread,      // arg = message text fragment — open its thread panel
        CloseThread, //
        Type,        // arg = text, num = characters per second (composer, or the focused field)
        Key,         // arg = Return | Tab | Escape | Down | Up | Backspace
        Send,        // press the send key in the focused composer
        React,       // arg = message text fragment, arg2 = emoji name
        Search,      // arg = query — open search, type it, run it
        CloseSearch, //
        QuickSwitch, // arg = text typed into the quick switcher, then Enter
        Theme,       // arg = light | dark
        Settings, // list = pages to walk (appearance|notifications|ai|storage|system|about), ms =
                  // per page
        MessageMenu,  // arg = message text fragment — right-click it
        ChannelMenu,  // arg = conversation id — right-click its sidebar row
        MenuHover,    // arg = item label of the open context menu
        MenuPick,     // arg = item label of the open context menu — click it
        CloseMenu,    //
        MoveToThread, // arg = message text fragment, arg2 = target root text fragment
        DialogButton, // arg = button label in the topmost dialog — click it
        CloseDialog,  //
        Gif,          // arg = GIF search query — open the picker, search, pick the first
        Play,         // arg = message text fragment — press play/pause on its audio clip
        OpenImage,    // arg = message text fragment — open its image in the viewer
        CloseImage,   //
        OpenThreads,  // click the roster's "Threads" entry — the threads overview page
        OpenSaved,    // click the roster's "Saved messages" entry
        Canvas,       // click the open conversation's canvas tab
        MessagesTab,  // click the "Messages" tab (back from the canvas)
        Post,         // conv + user + arg = mrkdwn: another user posts right now;
                      // arg2 = root text fragment → as a reply in that thread
        Quit,         //
    };
    Kind        kind;
    QString     arg;
    QString     arg2;
    QStringList list;
    QString     conv; // Post: conversation id
    QString     user; // Post: author id
    int         ms  = 0;
    double      num = 0;
};

struct TourScript {
    QSize                 window{1280, 800};
    int                   pauseMs = 700; // idle between steps
    std::vector<TourStep> steps;
};

// The --demo-tour / --demo-tour= argument; empty when absent.
QString tourPathFromArgs(int argc, char **argv);

// Parse a tour file: {"window":[w,h], "pause":700, "steps":[{"open":"C1"}, …]}.
std::optional<TourScript> loadTour(const QString &path, QString *error);
std::optional<TourScript> parseTour(const QByteArray &json, QString *error);

} // namespace demo
