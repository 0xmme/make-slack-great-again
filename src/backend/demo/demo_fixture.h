// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
// Demo fixture: the JSON that describes the fake workspace shown by `--demo`
// (see demo/README.md for the format), parsed into the domain structs the
// backend hands to Session. Times in the file are relative ("-2d 09:14", "+7m")
// so a recording made on any day looks like it happened this week.
#pragma once

#include "backend/domain.h"

#include <QDateTime>
#include <QString>
#include <optional>
#include <unordered_map>
#include <vector>

namespace demo {

// A canned reply the fake workspace posts after the user sends into `conv`:
// `typingMs` of "is typing…" (0 = none), then the message. Consumed in file
// order per conversation.
struct AutoReply {
    QString conv;
    UserId  user;
    QString text; // mrkdwn
    int     afterMs  = 1200;
    int     typingMs = 1500;
    // Answers a reply sent into a thread (and lands in that thread) instead of
    // a top-level send — so a scripted thread reply doesn't eat the channel's
    // canned answer.
    bool    inThread = false;
};

// A conversation's channel canvas ("canvas": {"title", "html"} on the
// conversation): the rendered document as Slack's url_private serves it — the
// inner HTML of <div class="quip-canvas-content">, read from a fixture file.
struct Canvas {
    QString conv;
    QString fileId;
    QString title;
    QString html;
};

// A link preview the fake workspace attaches to a sent message that contains
// `url` (prefix match), ~1 s after the send lands — like Slack's unfurl.
struct Unfurl {
    QString    url;
    Attachment attachment;
};

// Canned answer of the stand-in AI endpoint: used when the request body
// contains `match` (case-insensitive).
struct AiReply {
    QString match;
    QString text;
};

struct Fixture {
    QString        dir; // absolute fixture directory (asset paths resolve against it)
    QString        workspaceId;
    QString        workspaceName;
    QString        workspaceIcon; // file:// URL, may be empty
    UserId         me;
    ConversationId startConversation;

    std::vector<User>                                 users;
    std::vector<Conversation>                         conversations;
    // conv id → top-level messages, oldest first (thread replies excluded, as
    // conversations.history would).
    std::unordered_map<QString, std::vector<Message>> history;
    // threadKey(conv, rootTs) → replies, oldest first.
    std::unordered_map<QString, std::vector<Message>> threads;
    std::vector<AutoReply>                            autoReplies;
    std::vector<Canvas>                               canvases;
    std::vector<Unfurl>                               unfurls;
    std::vector<AiReply>                              aiReplies;
    QString                                           aiDefault;

    static QString threadKey(const ConversationId &conv, const Ts &root) {
        return conv.value + QLatin1Char('/') + root;
    }
};

// Parse `<dir>/fixture.json` (or the given .json file). `now` anchors the
// relative times; tests pass a fixed one. On failure returns nullopt and sets
// *error to a human-readable reason.
std::optional<Fixture> loadFixture(
    const QString &path, QString *error, const QDateTime &now = QDateTime::currentDateTime()
);

// Resolve a fixture time spec against `now` and the previous message's time:
//   "-2d 09:14"  two days before today at 09:14 (local)   "14:32"  today at 14:32
//   "-45m"       45 minutes before now  (s/m/h/d)          "+7m"    7 minutes after `prev`
// Returns an invalid QDateTime when the spec is malformed.
QDateTime parseTimeSpec(const QString &spec, const QDateTime &now, const QDateTime &prev);

// Slack-style "seconds.micros" ts for a point in time.
Ts tsFor(const QDateTime &when, int microOffset = 0);

// file:// URL for a fixture-relative asset path ("assets/avatars/mira.png").
QString assetUrl(const QString &dir, const QString &rel);

// A File record for a local file (mime/size/dimensions read from disk), with
// file:// URLs the message list loads directly. Also used for demo uploads.
File fileFromLocalPath(const QString &absPath, int index);

} // namespace demo
