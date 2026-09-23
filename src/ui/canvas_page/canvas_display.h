// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
// Display preparation of Slack canvas content, shared by the canvas editor
// (CanvasPage) and the message list's canvas preview card, so both show a
// canvas the same way.
#pragma once

#include <QString>

class QTextDocument;
class Session;

namespace CanvasDisplay {

// A canvas title as shown to the user. files.info / message file titles are
// entity-escaped and may carry emoji codes and <@U…> mentions (huddle notes:
// ":headphones: Huddle notes: 9/23/26 with <@U1> and <@U2>") — decode, expand
// the codes and resolve the mentions to "@name". Matches the text of the title
// <h1> in prepareHtml()'s output, so it can identify that h1.
QString title(const QString &raw, const Session *session);

// Canvas HTML (the url_private download) normalized for a QTextDocument, in
// ways that keep every section's markdown round-trippable (see
// CanvasDiff::normalizeMd, which reverses the mention anchors):
//  - standard-emoji <img data-is-slack> pictures are dropped in favour of the
//    ":code:" text Slack puts right after them, and every emoji code is then
//    expanded (CanvasEmoji::expandInHtml) — keeping both drew the emoji twice;
//  - <lnk href> hyperlinks become real <a> anchors;
//  - inline content images lose their placeholder width/height;
//  - bare "<a>@U…</a>" mentions become msga://user/<id> anchors labelled with
//    the member's name.
QString prepareHtml(const QString &rawHtml, const Session *session);

// Pixel size of a level-`level` canvas heading over `bodyPx` body text:
// +8 / +5 / +2 px for h1..h3, body size (bold) below that — at the editor's
// 15px body that is 23/20/17/15, all under its 28px title line.
int headingPx(int level, int bodyPx);

// Size the heading blocks of a document loaded from prepareHtml() output to
// headingPx(). Done per block because Qt's HTML engine ignores font-size on
// h1..h6 in a stylesheet and falls back to its oversized built-in
// multipliers. Display-only: the heading *level* (what toMarkdown emits as #)
// is untouched, so the editor's section diff is unaffected. Used by both the
// canvas editor and the message-list preview card, so they agree.
void styleHeadings(QTextDocument *doc, int bodyPx);

} // namespace CanvasDisplay
