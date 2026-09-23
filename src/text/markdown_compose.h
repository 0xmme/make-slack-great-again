// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
// Composer text → what goes on the Slack wire.
//
// People type CommonMark by habit — **bold**, ~~strike~~, [label](url),
// "- item" lists, ``` fences — while Slack speaks its own mrkdwn (*bold*,
// ~strike~, <url|label>, no list syntax at all) and needs a rich_text block
// for anything structural. Slack's server does not translate: a CommonMark
// message posted as-is shows its asterisks to everyone, which is what the
// official client quietly avoids by converting on the way out. convert() does
// the same here.
//
// Rules of the road:
//   • Existing mrkdwn passes through unchanged. *x* stays bold (Slack's own
//     bold), _x_ italic, ~x~ strike, `x` code, <@U…>/<#C…>/<!here>/<url|label>
//     tokens are opaque, __x__ is left for the composer's underline button.
//   • CommonMark that mrkdwn can express is rewritten: **x** → *x*,
//     ***x*** → *_x_*, ~~x~~ → ~x~, [label](url) → <url|label>, and a fence's
//     language hint (```js) is dropped since Slack would print it as code.
//   • Lists ("- a", "* a", "1. a", nested by indentation) are the one thing
//     mrkdwn cannot carry, so they become a rich_text_list; the `text`
//     fallback shows "• a" / "1. a" like the official client's own fallback.
//   • The rich_text block is built ONLY when the message has a list. For
//     everything else the mrkdwn `text` alone renders identically in every
//     client, and a block Slack rejects (invalid_blocks) fails the whole send,
//     so the block stays off the wire unless it earns its place.
//   • Headings and blockquotes stay literal mrkdwn (Slack has no heading;
//     ">" already quotes). Backslash escapes are not interpreted: mrkdwn has
//     none, and "\*" typed in Slack means a backslash.
//
// Line structure is preserved: Slack keeps a chat message's line layout, so a
// soft line break is a newline, not a space. Lazy list continuation is NOT
// CommonMark's — an unindented line after a list item ends the list (that is
// what a chat author means by it); an indented one continues the item.
#pragma once

#include "backend/domain.h"

#include <QJsonArray>

namespace MarkdownCompose {

struct Composed {
    // The `text` argument: mrkdwn. The optimistic copy renders this, edits
    // reopen it, and the lost-send reconcile compares it — so it is also what
    // Message::rawText holds for the sent message.
    QString    mrkdwn;
    // Block Kit `blocks`: empty, or exactly one rich_text block mirroring the
    // whole message (Slack renders blocks INSTEAD of text, never both).
    QJsonArray blocks;
    bool       operator==(const Composed &) const = default;
};

Composed convert(const QString &composerText);

// Take the GIF picker's links (<giphy-media-url|label>, see the composer) out of
// composer text, with a space the composer put around each, and return them in
// order — for a backend that posts a GIF as an image of its own rather than a
// link (Capabilities::gifAttachments). The label becomes the alt text. Any
// other link stays. `composerText` is left trimmed when a GIF was taken.
std::vector<OutgoingGif> takeGifLinks(QString &composerText);

// Only the inline rewrites (**x**, ~~x~~, [label](url)) on one line of text,
// code spans and Slack tokens left alone. Exposed for tests.
QString convertInline(const QString &line);

// Parsed text → rich_text inline elements ("text" with a style object, "user",
// "channel", "emoji", "link", "broadcast", "usergroup"), adjacent same-style
// runs merged. Exposed for tests.
QJsonArray richTextElements(const TextWithEntities &twe);

} // namespace MarkdownCompose
