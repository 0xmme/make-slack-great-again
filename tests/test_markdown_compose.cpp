// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 MSGA contributors. See LICENSE for details.
// Composer text → mrkdwn + rich_text: the CommonMark rewrites, what must stay
// literal, and the block shape Slack expects for lists.
#include <catch2/catch_test_macros.hpp>

#include "text/markdown_compose.h"
#include "text/mrkdwn_parser.h"

#include <QJsonDocument>
#include <QJsonObject>

using MarkdownCompose::convert;
using MarkdownCompose::convertInline;

namespace {

QString mrkdwn(const QString &in) {
    return convert(in).mrkdwn;
}

// The rich_text block's element list, or an empty array when no block was built.
QJsonArray elements(const MarkdownCompose::Composed &c) {
    if (c.blocks.isEmpty())
        return {};
    return c.blocks[0].toObject().value("elements").toArray();
}

QJsonArray richText(const QString &mrkdwn) {
    return MarkdownCompose::richTextElements(MrkdwnParser::parse(mrkdwn));
}

QString json(const QJsonArray &a) {
    return QString::fromUtf8(QJsonDocument(a).toJson(QJsonDocument::Compact));
}

} // namespace

// ── Inline rewrites ───────────────────────────────────────────────────────────

TEST_CASE("plain text and existing mrkdwn pass through untouched", "[compose][inline]") {
    for (const char *s :
         {"hello world",
          "*bold* and _italic_ and ~strike~",
          "`code` and ```pre```",
          "__under__",
          "<@U123> <#C1|general> <!here> <https://x.io|label> <https://x.io>",
          ":smile: 5 * 3 * 2",
          "a ** b ** c",
          "5 ** 2",
          "**",
          "***",
          "not a [link](nowhere)",
          "[1](a)"}) {
        CHECK(mrkdwn(s) == QString::fromUtf8(s));
        CHECK(convert(s).blocks.isEmpty());
    }
}

TEST_CASE("**bold** and ~~strike~~ become Slack's single marks", "[compose][inline]") {
    CHECK(convertInline("**bold**") == "*bold*");
    CHECK(convertInline("say **bold** twice **more**") == "say *bold* twice *more*");
    CHECK(convertInline("~~gone~~") == "~gone~");
    CHECK(convertInline("**~~both~~**") == "*~both~*");
    CHECK(convertInline("***shout***") == "*_shout_*");
    // CommonMark flanking: the opener touches text, the closer follows text.
    CHECK(convertInline("** spaced **") == "** spaced **");
    CHECK(convertInline("**a** and **b **") == "*a* and **b **");
}

TEST_CASE("single *x* stays literal — it is already Slack bold", "[compose][inline]") {
    CHECK(convertInline("*x*") == "*x*");
    CHECK(convertInline("_x_") == "_x_");
    CHECK(convertInline("~x~") == "~x~");
}

TEST_CASE("[label](url) becomes <url|label>", "[compose][inline]") {
    CHECK(convertInline("see [docs](https://example.com/a)") == "see <https://example.com/a|docs>");
    CHECK(convertInline("[mail](mailto:a@b.c)") == "<mailto:a@b.c|mail>");
    CHECK(convertInline("![shot](https://x.io/i.png)") == "<https://x.io/i.png|shot>");
    CHECK(convertInline(R"([t](https://x.io/p "title"))") == "<https://x.io/p|t>"); // title dropped
    CHECK(
        convertInline("[wiki](https://en.wikipedia.org/wiki/Foo_(bar))") ==
        "<https://en.wikipedia.org/wiki/Foo_(bar)|wiki>"
    );
    // Same label as URL, or a pipe in the URL: bare token.
    CHECK(convertInline("[https://x.io](https://x.io)") == "<https://x.io>");
    CHECK(convertInline("[a](https://x.io/?a=1|2)") == "<https://x.io/?a=1|2>");
    // A pipe or '>' in the label would end the token early.
    CHECK(convertInline("[a|b>c](https://x.io)") == "<https://x.io|a/b&gt;c>");
    // No scheme, no link.
    CHECK(convertInline("[a](b)") == "[a](b)");
}

TEST_CASE("code spans and Slack tokens shield their content", "[compose][inline]") {
    CHECK(convertInline("`**raw**`") == "`**raw**`");
    CHECK(convertInline("``a ` **b** ``") == "``a ` **b** ``");
    CHECK(convertInline("`unclosed **x**") == "`unclosed *x*");
    CHECK(convertInline("<https://x.io|**not bold**>") == "<https://x.io|**not bold**>");
    CHECK(convertInline("<@U1> **yes**") == "<@U1> *yes*");
    // A literal "<word>" is not a token and stays open to rewrites.
    CHECK(convertInline("<b> **x**") == "<b> *x*");
}

// ── Blocks: lists ─────────────────────────────────────────────────────────────

TEST_CASE("a bulleted list becomes a rich_text_list with a bullet fallback", "[compose][list]") {
    const auto c = convert("- one\n- **two**\n* three");
    CHECK(c.mrkdwn == "• one\n• *two*\n• three");
    REQUIRE(c.blocks.size() == 1);
    CHECK(c.blocks[0].toObject().value("type").toString() == "rich_text");
    const auto els = elements(c);
    REQUIRE(els.size() == 1);
    const auto list = els[0].toObject();
    CHECK(list.value("type").toString() == "rich_text_list");
    CHECK(list.value("style").toString() == "bullet");
    CHECK(!list.contains("indent"));
    const auto items = list.value("elements").toArray();
    REQUIRE(items.size() == 3);
    CHECK(items[0].toObject().value("type").toString() == "rich_text_section");
    CHECK(
        json(items[1].toObject().value("elements").toArray()) ==
        R"([{"style":{"bold":true},"text":"two","type":"text"}])"
    );
}

TEST_CASE(
    "an ordered list renumbers its fallback and carries the start as offset", "[compose][list]"
) {
    const auto c = convert("3. a\n7. b");
    CHECK(c.mrkdwn == "3. a\n4. b");
    const auto list = elements(c)[0].toObject();
    CHECK(list.value("style").toString() == "ordered");
    CHECK(list.value("offset").toInt() == 2);

    const auto from1 = convert("1. a\n2. b\n3) c");
    CHECK(from1.mrkdwn == "1. a\n2. b\n3. c");
    CHECK(!elements(from1)[0].toObject().contains("offset"));
}

TEST_CASE("nested items become sibling lists with an indent", "[compose][list]") {
    // Two-space and four-space nesting rank the same.
    for (const char *in : {"- a\n  - b\n  - c\n- d", "- a\n    - b\n    - c\n- d"}) {
        const auto c   = convert(in);
        const auto els = elements(c);
        REQUIRE(els.size() == 3);
        CHECK(els[0].toObject().value("elements").toArray().size() == 1);
        CHECK(els[1].toObject().value("indent").toInt() == 1);
        CHECK(els[1].toObject().value("elements").toArray().size() == 2);
        CHECK(!els[2].toObject().contains("indent"));
        CHECK(c.mrkdwn == "• a\n    • b\n    • c\n• d");
    }
    // A style change at the same level also starts a new list element.
    CHECK(elements(convert("- a\n1. b")).size() == 2);
}

TEST_CASE("text around a list lands in sections and the blank lines survive", "[compose][list]") {
    const auto c = convert("intro **x**\n\n- a\n- b\n\noutro\n\nlast");
    CHECK(c.mrkdwn == "intro *x*\n\n• a\n• b\n\noutro\n\nlast");
    const auto els = elements(c);
    REQUIRE(els.size() == 3);
    CHECK(els[0].toObject().value("type").toString() == "rich_text_section");
    CHECK(els[1].toObject().value("type").toString() == "rich_text_list");
    // One section per paragraph run; the blank line inside it is kept as text.
    CHECK(
        json(els[2].toObject().value("elements").toArray()) ==
        R"([{"text":"outro\n\nlast","type":"text"}])"
    );
}

TEST_CASE(
    "a list ends at an unindented line, continues past indented ones and blanks", "[compose][list]"
) {
    const auto c = convert("- a\n  more a\n- b\n\n- c\nafter");
    CHECK(c.mrkdwn == "• a\nmore a\n• b\n• c\nafter");
    const auto els = elements(c);
    REQUIRE(els.size() == 2);
    const auto items = els[0].toObject().value("elements").toArray();
    REQUIRE(items.size() == 3);
    CHECK(
        json(items[0].toObject().value("elements").toArray()) ==
        R"([{"text":"a\nmore a","type":"text"}])"
    );
}

TEST_CASE("what is not a list marker", "[compose][list]") {
    for (const char *s : {"-5 degrees", "-item", "1.5 hours", "**bold** start", "- ", "a - b"})
        CHECK(convert(s).blocks.isEmpty());
}

TEST_CASE("list items resolve Slack tokens and emoji into typed elements", "[compose][list]") {
    const auto items = elements(convert(
        "- hi <@U1> in <#C1|general> <!here> :+1::skin-tone-3: "
        "[d](https://x.io) <!subteam^S1|@team> <!everyone>"
    ))[0]
                           .toObject()
                           .value("elements")
                           .toArray();
    REQUIRE(items.size() == 1);
    CHECK(
        json(items[0].toObject().value("elements").toArray()) ==
        R"([{"text":"hi ","type":"text"},{"type":"user","user_id":"U1"},{"text":" in ","type":"text"},)"
        R"({"channel_id":"C1","type":"channel"},{"text":" ","type":"text"},{"range":"here","type":"broadcast"},)"
        R"({"text":" ","type":"text"},{"name":"+1","skin_tone":3,"type":"emoji"},{"text":" ","type":"text"},)"
        R"({"text":"d","type":"link","url":"https://x.io"},{"text":" ","type":"text"},)"
        R"({"type":"usergroup","usergroup_id":"S1"},{"text":" ","type":"text"},{"range":"everyone","type":"broadcast"}])"
    );
}

TEST_CASE("a label-less user-group mention becomes a usergroup element", "[compose][list]") {
    const auto items =
        elements(convert("- <!subteam^S1> ping"))[0].toObject().value("elements").toArray();
    REQUIRE(items.size() == 1);
    CHECK(
        json(items[0].toObject().value("elements").toArray()) ==
        R"([{"type":"usergroup","usergroup_id":"S1"},{"text":" ping","type":"text"}])"
    );
}

// ── Blocks: fences and quotes ─────────────────────────────────────────────────

TEST_CASE("fenced code passes through, loses only a language hint", "[compose][pre]") {
    CHECK(mrkdwn("```\nx = 1\n```") == "```\nx = 1\n```");
    CHECK(mrkdwn("```js\nx = 1\n```") == "```\nx = 1\n```");
    CHECK(mrkdwn("```ls -la\nfoo```") == "```\nls -la\nfoo\n```"); // mrkdwn habit: content
    CHECK(mrkdwn("```one-liner```") == "```one-liner```");
    CHECK(mrkdwn("```\n- not a list\n**raw**\n```") == "```\n- not a list\n**raw**\n```");
    CHECK(mrkdwn("```\nunterminated **x**") == "```\nunterminated *x*");
    CHECK(mrkdwn("```\ncode\n``` **tail**") == "```\ncode\n```\n*tail*");
}

TEST_CASE("fences and quotes take their block shapes when a list is present", "[compose][pre]") {
    const auto c   = convert("- a\n```py\nprint(1)\n```\n> **q**\n> &lt;two&gt;");
    const auto els = elements(c);
    REQUIRE(els.size() == 3);
    CHECK(
        json(QJsonArray{els[1]}) ==
        R"j([{"elements":[{"text":"print(1)","type":"text"}],"type":"rich_text_preformatted"}])j"
    );
    CHECK(
        json(QJsonArray{els[2]}) ==
        R"([{"elements":[{"style":{"bold":true},"text":"q","type":"text"},{"text":"\n<two>","type":"text"}],"type":"rich_text_quote"}])"
    );
    CHECK(c.mrkdwn == "• a\n```\nprint(1)\n```\n> *q*\n> &lt;two&gt;");
}

TEST_CASE("without a list, no block is built even for code or quotes", "[compose]") {
    CHECK(convert("> q\n```\nc\n```\n**b**").blocks.isEmpty());
    CHECK(convert("").mrkdwn.isEmpty());
    CHECK(convert("").blocks.isEmpty());
    CHECK(mrkdwn("a\r\nb") == "a\nb");
}

// ── richTextElements on its own ───────────────────────────────────────────────

TEST_CASE("nested marks compose their styles and merge equal runs", "[compose][elements]") {
    CHECK(
        json(richText("*a _b_ c* d")) ==
        R"([{"style":{"bold":true},"text":"a ","type":"text"},{"style":{"bold":true,"italic":true},"text":"b","type":"text"},)"
        R"({"style":{"bold":true},"text":" c","type":"text"},{"text":" d","type":"text"}])"
    );
    CHECK(
        json(richText("`x` ~y~")) ==
        R"([{"style":{"code":true},"text":"x","type":"text"},{"text":" ","type":"text"},{"style":{"strike":true},"text":"y","type":"text"}])"
    );
}

TEST_CASE("a styled mention keeps bold; a code span keeps tokens literal", "[compose][elements]") {
    CHECK(
        json(richText("*<@U1>* `<https://x.io|l>`")) ==
        R"([{"style":{"bold":true},"type":"user","user_id":"U1"},{"text":" ","type":"text"},)"
        R"({"style":{"code":true},"text":"<https://x.io|l>","type":"text"}])"
    );
    CHECK(json(richText("`<@U1>`")) == R"([{"style":{"code":true},"text":"<@U1>","type":"text"}])");
}

TEST_CASE("a bare <word> is given back as text, a bare URL as a link", "[compose][elements]") {
    CHECK(json(richText("<word>")) == R"([{"text":"<word>","type":"text"}])");
    CHECK(json(richText("<https://x.io>")) == R"([{"type":"link","url":"https://x.io"}])");
    CHECK(json(richText("__u__")) == R"([{"text":"u","type":"text"}])");
}

// ── takeGifLinks ──────────────────────────────────────────────────────────────
//
// The composer's GIF picker leaves <giphy-url|label> in the text; on Slack it
// goes out as an attachment instead, like the official picker sends it.

TEST_CASE("a picked GIF is taken out of the text with its label", "[compose][gif]") {
    QString    text = "look <https://media2.giphy.com/media/abc/200w.gif|Happy Dancing> nice";
    const auto gifs = MarkdownCompose::takeGifLinks(text);
    REQUIRE(gifs.size() == 1);
    CHECK(gifs[0].url == "https://media2.giphy.com/media/abc/200w.gif");
    CHECK(gifs[0].altText == "Happy Dancing");
    CHECK(text == "look nice"); // one of the spaces around the badge goes with it
}

TEST_CASE("a message that is only a GIF leaves no text", "[compose][gif]") {
    QString    text = "<https://media.giphy.com/media/abc/200w.gif> ";
    const auto gifs = MarkdownCompose::takeGifLinks(text);
    REQUIRE(gifs.size() == 1);
    CHECK(gifs[0].altText.isEmpty());
    CHECK(text.isEmpty());
}

TEST_CASE("several GIFs come out in order", "[compose][gif]") {
    QString    text = "hey <https://i.giphy.com/one.gif|One> and <https://i.giphy.com/two.gif|Two>";
    const auto gifs = MarkdownCompose::takeGifLinks(text);
    REQUIRE(gifs.size() == 2);
    CHECK(gifs[0].url == "https://i.giphy.com/one.gif");
    CHECK(gifs[1].url == "https://i.giphy.com/two.gif");
    CHECK(text == "hey and");
}

TEST_CASE("other links, and giphy pages, stay in the text", "[compose][gif]") {
    // Only a GIPHY media asset is a GIF; the site itself unfurls as a page.
    QString       text = " <https://example.com/x.gif|pic> <https://giphy.com/gifs/cat-abc|cats> ";
    const QString before = text;
    CHECK(MarkdownCompose::takeGifLinks(text).empty());
    CHECK(text == before); // untouched, not even trimmed
}
