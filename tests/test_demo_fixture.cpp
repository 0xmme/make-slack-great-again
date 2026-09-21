// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 MSGA contributors. See LICENSE for details.
// demo::loadFixture (the --demo workspace description) and the interactive
// bits of demo::DemoBackend built on it.
#include <catch2/catch_test_macros.hpp>
#include "backend/demo/demo_backend.h"
#include "backend/demo/demo_fixture.h"
#include "backend/demo/demo_services.h"
#include "backend/demo/demo_tour_script.h"
#include "network/gif_search.h"

#include <QCoreApplication>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QTemporaryDir>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimeZone>
#include <QUrl>
#include "llm/llm_wire.h"

using namespace demo;

namespace {

const QDateTime kNow(QDate(2026, 9, 21), QTime(16, 0), QTimeZone::systemTimeZone());

QString writeFixture(const QTemporaryDir &dir, const QByteArray &json) {
    QFile f(dir.filePath("fixture.json"));
    REQUIRE(f.open(QIODevice::WriteOnly));
    f.write(json);
    f.close();
    QFile csv(dir.filePath("data.csv"));
    REQUIRE(csv.open(QIODevice::WriteOnly));
    csv.write("a,b\n1,2\n");
    return dir.path();
}

const QByteArray kMinimal = R"({
  "workspace": {"id": "T1", "name": "Acme"},
  "me": "U1",
  "startConversation": "C2",
  "users": [
    {"id": "U1", "name": "me", "displayName": "Me", "tz": "+02:00"},
    {"id": "U2", "name": "mira", "displayName": "Mira", "active": true, "status": {"emoji": "art", "text": "Busy"}}
  ],
  "conversations": [
    {"id": "C1", "kind": "channel", "name": "general", "unread": 1},
    {"id": "C2", "kind": "channel", "name": "design"},
    {"id": "D1", "kind": "dm", "user": "U2", "unread": 5},
    {"id": "G1", "kind": "group", "members": ["U2"]}
  ],
  "messages": [
    {"conv": "C1", "user": "U2", "time": "-1d 09:00", "text": "first *bold* <@U1>",
     "reactions": [{"name": "tada", "users": ["U1", "U2"]}],
     "replies": [
       {"user": "U1", "time": "+10m", "text": "reply one"},
       {"user": "U2", "time": "+5m", "text": "reply two"}
     ]},
    {"conv": "C1", "user": "U1", "time": "-1d 09:30", "text": "second", "files": [{"path": "data.csv"}]},
    {"conv": "C1", "user": "U2", "time": "-1d 08:00", "text": "actually the oldest"},
    {"conv": "D1", "user": "U2", "time": "-30m", "text": "dm"},
    {"conv": "C2", "user": "U2", "time": "-20m", "text": "",
     "files": [{"path": "data.csv", "name": "Voice note", "subtype": "slack_audio", "durationMs": 3000, "transcript": "hello there"}]}
  ],
  "unfurls": [
    {"url": "https://example.test/doc", "service": "Docs", "title": "A doc", "text": "preview", "color": "#123456"}
  ],
  "ai": {
    "default": "generic summary",
    "replies": [{"match": "palette", "text": "palette summary"}]
  },
  "autoReplies": [
    {"conv": "C2", "user": "U2", "afterMs": 0, "typingMs": 0, "text": "canned"}
  ]
})";

template <typename T>
T collect(auto producer) {
    T             out{};
    rpl::lifetime lt;
    std::move(producer) | rpl::on_next([&out](T v) { out = std::move(v); }, lt);
    return out;
}

// Pump the event loop until `pred` holds or `ms` elapse.
bool waitFor(const std::function<bool()> &pred, int ms = 2000) {
    QElapsedTimer t;
    t.start();
    while (!pred() && t.elapsed() < ms)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 20);
    return pred();
}

} // namespace

// ── time specs ────────────────────────────────────────────────────────────────

TEST_CASE("parseTimeSpec: wall clock with day offset", "[demo][fixture]") {
    const QDateTime prev;
    CHECK(parseTimeSpec("-2d 09:14", kNow, prev) == QDateTime(QDate(2026, 9, 19), QTime(9, 14)));
    CHECK(parseTimeSpec("09:14", kNow, prev) == QDateTime(QDate(2026, 9, 21), QTime(9, 14)));
    CHECK(parseTimeSpec("0d 23:59", kNow, prev) == QDateTime(QDate(2026, 9, 21), QTime(23, 59)));
}

TEST_CASE("parseTimeSpec: relative to now and to the previous message", "[demo][fixture]") {
    const QDateTime prev = kNow.addSecs(-3600);
    CHECK(parseTimeSpec("-45m", kNow, prev) == kNow.addSecs(-45 * 60));
    CHECK(parseTimeSpec("-2h", kNow, prev) == kNow.addSecs(-7200));
    CHECK(parseTimeSpec("-3d", kNow, prev) == kNow.addDays(-3));
    CHECK(parseTimeSpec("+7m", kNow, prev) == prev.addSecs(7 * 60));
    CHECK(parseTimeSpec("+90s", kNow, {}) == kNow.addSecs(90)); // no prev → now
}

TEST_CASE("parseTimeSpec: malformed specs are invalid", "[demo][fixture]") {
    CHECK_FALSE(parseTimeSpec("yesterday", kNow, {}).isValid());
    CHECK_FALSE(parseTimeSpec("25:99", kNow, {}).isValid());
    CHECK_FALSE(parseTimeSpec("", kNow, {}).isValid());
}

TEST_CASE("tsFor renders seconds.micros", "[demo][fixture]") {
    const QDateTime t = QDateTime::fromMSecsSinceEpoch(1758445200123);
    CHECK(tsFor(t) == "1758445200.123000");
    CHECK(tsFor(t, 7) == "1758445200.123007");
}

// ── loadFixture ───────────────────────────────────────────────────────────────

TEST_CASE("loadFixture: workspace, users and conversations", "[demo][fixture]") {
    QTemporaryDir dir;
    QString       err;
    const auto    fx = loadFixture(writeFixture(dir, kMinimal), &err, kNow);
    REQUIRE(fx.has_value());
    CHECK(err.isEmpty());
    CHECK(fx->workspaceId == "T1");
    CHECK(fx->workspaceName == "Acme");
    CHECK(fx->me.value == "U1");
    CHECK(fx->startConversation.value == "C2");

    REQUIRE(fx->users.size() == 2);
    CHECK(fx->users[0].hasTz);
    CHECK(fx->users[0].tzOffset == 7200);
    CHECK(fx->users[1].isActive);
    CHECK(fx->users[1].statusEmoji == "art");
    CHECK(fx->users[1].teamId == "T1");

    REQUIRE(fx->conversations.size() == 4);
    const auto &dm = fx->conversations[2];
    CHECK(dm.kind == ConvKind::Im);
    CHECK(dm.dmUser == UserId{"U2"});
    CHECK(dm.name == "mira"); // defaulted to the peer's handle
    const auto &group = fx->conversations[3];
    CHECK(group.kind == ConvKind::Mpim);
    CHECK(group.members.size() == 2); // me appended
    CHECK(group.name == "mpdm-mira--me-1");
}

TEST_CASE("loadFixture: history is sorted, threaded and cursor-derived", "[demo][fixture]") {
    QTemporaryDir dir;
    QString       err;
    const auto    fx = loadFixture(writeFixture(dir, kMinimal), &err, kNow);
    REQUIRE(fx.has_value());

    const auto &c1 = fx->history.at("C1");
    REQUIRE(c1.size() == 3);
    CHECK(c1[0].text.text == "actually the oldest"); // sorted oldest-first regardless of file order
    CHECK(c1[1].text.text.startsWith("first bold "));
    REQUIRE(c1[1].text.entities.size() == 2); // Bold + the mention (resolved by Session later)
    CHECK(c1[1].text.entities[1].type == EntityType::UserMention);
    CHECK(c1[1].text.entities[1].data == "U1");
    CHECK(c1[2].text.text == "second");
    CHECK(c1[0].date < c1[1].date);
    CHECK(c1[1].date < c1[2].date);
    CHECK(c1[1].rawText == "first *bold* <@U1>");
    REQUIRE(c1[1].reactions.size() == 1);
    CHECK(c1[1].reactions[0].count == 2);

    // Thread wiring on the root and the replies.
    CHECK(c1[1].replyCount == 2);
    CHECK(c1[1].replyUsers.size() == 2);
    const auto &replies = fx->threads.at(Fixture::threadKey(ConversationId{"C1"}, c1[1].ts));
    REQUIRE(replies.size() == 2);
    CHECK(replies[0].threadRoot == c1[1].ts);
    CHECK(replies[0].parentUserId == UserId{"U2"});
    CHECK(
        replies[1].date - replies[0].date == 5 * 60 * 1000000LL
    ); // "+5m" after the previous reply
    CHECK(c1[1].latestReply == replies[1].ts);

    // File chip built from the local csv.
    REQUIRE(c1[2].files.size() == 1);
    CHECK(c1[2].files[0].name == "data.csv");
    CHECK(c1[2].files[0].size == 8);
    CHECK(c1[2].files[0].urlPrivate.startsWith("file://"));
    CHECK(c1[2].files[0].isCsv());

    // unread=1 → lastRead is the second-newest; latestTs the newest.
    const auto &conv = fx->conversations[0];
    CHECK(conv.latestTs == c1[2].ts);
    CHECK(conv.lastRead == c1[1].ts);
    // unread larger than the history → "0" (everything unread).
    CHECK(fx->conversations[2].lastRead == "0");
    // no unread → lastRead is the newest.
    CHECK(fx->conversations[1].lastRead == fx->history.at("C2").back().ts);
}

TEST_CASE("loadFixture: errors are reported, not swallowed", "[demo][fixture]") {
    QTemporaryDir dir;
    QString       err;

    CHECK_FALSE(loadFixture(dir.filePath("missing"), &err, kNow).has_value());
    CHECK(err.contains("cannot open"));

    QByteArray badUser = kMinimal;
    badUser.replace("\"user\": \"U2\", \"time\": \"-30m\"", "\"user\": \"U9\", \"time\": \"-30m\"");
    CHECK_FALSE(loadFixture(writeFixture(dir, badUser), &err, kNow).has_value());
    CHECK(err.contains("unknown user U9"));

    QByteArray badTime = kMinimal;
    badTime.replace("\"time\": \"-30m\"", "\"time\": \"noon\"");
    CHECK_FALSE(loadFixture(writeFixture(dir, badTime), &err, kNow).has_value());
    CHECK(err.contains("bad time noon"));

    QByteArray noMe = kMinimal;
    noMe.replace("\"me\": \"U1\"", "\"me\": \"U7\"");
    CHECK_FALSE(loadFixture(writeFixture(dir, noMe), &err, kNow).has_value());
    CHECK(err.contains("not in users"));
}

TEST_CASE("the shipped demo fixture loads", "[demo][fixture]") {
    QString    err;
    const auto fx = loadFixture(QStringLiteral(MSGA_DEMO_FIXTURE_DIR), &err, kNow);
    REQUIRE(fx.has_value());
    CHECK(err.isEmpty());
    CHECK(fx->users.size() >= 5);
    CHECK(fx->conversations.size() >= 5);
    CHECK_FALSE(fx->threads.empty());
    // Every referenced asset exists on disk.
    for (const auto &u : fx->users)
        if (!u.avatarUrl.isEmpty())
            CHECK(QFile::exists(QUrl(u.avatarUrl).toLocalFile()));
    for (const auto &[conv, msgs] : fx->history)
        for (const auto &m : msgs)
            for (const auto &f : m.files)
                CHECK(QFile::exists(QUrl(f.urlPrivate).toLocalFile()));
}

// ── DemoBackend ───────────────────────────────────────────────────────────────

TEST_CASE("DemoBackend: reads complete asynchronously with fixture data", "[demo][backend]") {
    int              argc   = 1;
    char             arg0[] = "test";
    char            *argv[] = {arg0, nullptr};
    QCoreApplication app(argc, argv);

    QTemporaryDir dir;
    QString       err;
    auto          fx = loadFixture(writeFixture(dir, kMinimal), &err, kNow);
    REQUIRE(fx.has_value());
    DemoBackend be(*fx);

    std::optional<std::vector<Conversation>> convs;
    rpl::lifetime                            lt;
    be.loadConversations() | rpl::on_next([&](std::vector<Conversation> v) { convs = v; }, lt);
    CHECK_FALSE(convs.has_value()); // not synchronous — see DemoBackend::later
    REQUIRE(waitFor([&] { return convs.has_value(); }));
    CHECK(convs->size() == 4);

    std::optional<MessagePage> thread;
    const Ts                   root = fx->history.at("C1")[1].ts;
    be.loadThread(ConversationId{"C1"}, root, std::nullopt) |
        rpl::on_next([&](MessagePage p) { thread = p; }, lt);
    REQUIRE(waitFor([&] { return thread.has_value(); }));
    REQUIRE(thread->messages.size() == 3); // root + 2 replies, like conversations.replies
    CHECK(thread->messages[0].ts == root);
    CHECK(thread->messages[1].text.text == "reply one");

    std::optional<std::vector<SearchResult>> hits;
    be.searchMessages("REPLY") | rpl::on_next([&](std::vector<SearchResult> r) { hits = r; }, lt);
    REQUIRE(waitFor([&] { return hits.has_value(); }));
    CHECK(hits->size() == 2);
    CHECK(hits->front().convName == "general");
}

TEST_CASE(
    "DemoBackend: a send lands, is confirmed, and draws the canned reply", "[demo][backend]"
) {
    int              argc   = 1;
    char             arg0[] = "test";
    char            *argv[] = {arg0, nullptr};
    QCoreApplication app(argc, argv);

    QTemporaryDir dir;
    QString       err;
    auto          fx = loadFixture(writeFixture(dir, kMinimal), &err, kNow);
    REQUIRE(fx.has_value());
    DemoBackend be(*fx);

    std::vector<Event> events;
    rpl::lifetime      lt;
    be.events() | rpl::on_next([&](Event e) { events.push_back(std::move(e)); }, lt);

    bool confirmed = false;
    be.sendMessage(
        ConversationId{"C2"}, OutgoingMessage{.rawText = "hello *there*"}, [&](bool ok, QString) {
            confirmed = ok;
        }
    );
    CHECK_FALSE(confirmed); // async, like a real round trip
    REQUIRE(waitFor([&] { return confirmed; }));

    // Own message arrives as EvMessageNew with our id and the parsed text…
    REQUIRE(waitFor([&] { return events.size() >= 2; }));
    const auto *own = std::get_if<EvMessageNew>(&events[0]);
    REQUIRE(own);
    CHECK(own->conv.value == "C2");
    CHECK(own->msg.author.value == "U1");
    CHECK(own->msg.text.text == "hello there");
    CHECK(own->msg.rawText == "hello *there*");
    // …then the fixture's autoReply for C2, from U2.
    const auto *reply = std::get_if<EvMessageNew>(&events[1]);
    REQUIRE(reply);
    CHECK(reply->msg.author.value == "U2");
    CHECK(reply->msg.text.text == "canned");
    CHECK(reply->msg.ts > own->msg.ts);

    // The reply is consumed: a second send gets no second canned answer.
    events.clear();
    confirmed = false;
    be.sendMessage(
        ConversationId{"C2"}, OutgoingMessage{.rawText = "again"}, [&](bool ok, QString) {
            confirmed = ok;
        }
    );
    REQUIRE(waitFor([&] { return confirmed; }));
    CHECK_FALSE(waitFor([&] { return events.size() >= 2; }, 300));
    CHECK(events.size() == 1);
}

TEST_CASE("DemoBackend: reactions, edits, deletes round-trip through events", "[demo][backend]") {
    int              argc   = 1;
    char             arg0[] = "test";
    char            *argv[] = {arg0, nullptr};
    QCoreApplication app(argc, argv);

    QTemporaryDir dir;
    QString       err;
    auto          fx = loadFixture(writeFixture(dir, kMinimal), &err, kNow);
    REQUIRE(fx.has_value());
    DemoBackend be(*fx);

    std::vector<Event> events;
    rpl::lifetime      lt;
    be.events() | rpl::on_next([&](Event e) { events.push_back(std::move(e)); }, lt);

    const ConversationId c1{"C1"};
    const Ts             root = fx->history.at("C1")[1].ts;

    be.addReaction(c1, root, "eyes");
    REQUIRE(events.size() == 1);
    CHECK(std::get<EvReactionAdded>(events[0]).user.value == "U1");
    be.addReaction(c1, root, "eyes"); // idempotent per user
    be.removeReaction(c1, root, "eyes");
    CHECK(std::holds_alternative<EvReactionRemoved>(events.back()));

    be.editMessage(c1, root, TextWithEntities{"edited", {}});
    const auto *changed = std::get_if<EvMessageChanged>(&events.back());
    REQUIRE(changed);
    CHECK(changed->msg.text.text == "edited");
    CHECK(changed->msg.edited);
    CHECK(changed->textOnly);

    // Deleting a reply shrinks the root's count; deleting the root drops its thread.
    const auto replies = fx->threads.at(Fixture::threadKey(c1, root));
    be.deleteMessage(c1, replies[0].ts);
    const auto *del = std::get_if<EvMessageDeleted>(&events.back());
    REQUIRE(del);
    CHECK(del->threadRoot == root);
    std::optional<MessagePage> thread;
    be.loadThread(c1, root, std::nullopt) | rpl::on_next([&](MessagePage p) { thread = p; }, lt);
    REQUIRE(waitFor([&] { return thread.has_value(); }));
    CHECK(thread->messages.size() == 2); // root + the one remaining reply
    CHECK(thread->messages[0].replyCount == 1);

    be.deleteMessage(c1, root);
    std::optional<MessagePage> gone;
    be.loadThread(c1, root, std::nullopt) | rpl::on_next([&](MessagePage p) { gone = p; }, lt);
    REQUIRE(waitFor([&] { return gone.has_value(); }));
    CHECK(gone->messages.empty());
}

// ── tour script ───────────────────────────────────────────────────────────────

TEST_CASE("parseTour: verbs, values and defaults", "[demo][tour]") {
    QString    err;
    const auto t = parseTour(
        R"({
      "window": [1280, 800], "pause": 500,
      "steps": [
        {"wait": 1200},
        {"open": "C1"},
        {"scroll": -520},
        {"type": "hello, world", "cps": 24},
        {"cps": 10, "type": "keys in any order"},
        {"send": true},
        {"react": ["hero", "raised_hands"]},
        {"theme": "dark"},
        {"settings": true},
        {"quit": true}
      ]})",
        &err
    );
    REQUIRE(t.has_value());
    CHECK(err.isEmpty());
    CHECK(t->window == QSize(1280, 800));
    CHECK(t->pauseMs == 500);
    REQUIRE(t->steps.size() == 10);
    using K = TourStep::Kind;
    CHECK(t->steps[0].kind == K::Wait);
    CHECK(t->steps[0].ms == 1200);
    CHECK(t->steps[1].kind == K::Open);
    CHECK(t->steps[1].arg == "C1");
    CHECK(t->steps[2].kind == K::Scroll);
    CHECK(t->steps[2].num == -520);
    CHECK(t->steps[3].kind == K::Type);
    CHECK(t->steps[3].arg == "hello, world");
    CHECK(t->steps[3].num == 24);
    CHECK(t->steps[4].kind == K::Type); // "cps" sorts before "type" in a QJsonObject
    CHECK(t->steps[4].num == 10);
    CHECK(t->steps[6].kind == K::React);
    CHECK(t->steps[6].arg == "hero");
    CHECK(t->steps[6].arg2 == "raised_hands");
    CHECK(t->steps[8].kind == K::Settings);
    CHECK(t->steps[8].ms == 2500); // default hold
    CHECK(t->steps[9].kind == K::Quit);
}

TEST_CASE("parseTour: rejects what the tour could not perform", "[demo][tour]") {
    QString err;
    CHECK_FALSE(parseTour(R"({"steps": [{"dance": 1}]})", &err).has_value());
    CHECK(err.contains("unknown verb"));
    CHECK_FALSE(parseTour(R"({"steps": [{"theme": "sepia"}]})", &err).has_value());
    CHECK(err.contains("light|dark"));
    CHECK_FALSE(parseTour(R"({"steps": [{"react": ["only text"]}]})", &err).has_value());
    CHECK(err.contains("react needs"));
    CHECK_FALSE(parseTour(R"({"steps": [{"open": ""}]})", &err).has_value());
    CHECK(err.contains("needs a value"));
    CHECK_FALSE(
        parseTour(R"({"window": [300, 200], "steps": [{"quit": true}]})", &err).has_value()
    );
    CHECK(err.contains("800x600"));
    CHECK_FALSE(parseTour(R"({"steps": []})", &err).has_value());
    CHECK(err.contains("no steps"));
    CHECK_FALSE(parseTour("not json", &err).has_value());
}

TEST_CASE("the shipped tour script parses", "[demo][tour]") {
    QString    err;
    const auto t = loadTour(QStringLiteral(MSGA_DEMO_FIXTURE_DIR "/tour.json"), &err);
    REQUIRE(t.has_value());
    CHECK(err.isEmpty());
    CHECK(t->steps.back().kind == TourStep::Kind::Quit);
}

// ── unfurls, ai, audio ────────────────────────────────────────────────────────

TEST_CASE("loadFixture: unfurls, ai replies and voice clips", "[demo][fixture]") {
    QTemporaryDir dir;
    QString       err;
    const auto    fx = loadFixture(writeFixture(dir, kMinimal), &err, kNow);
    REQUIRE(fx.has_value());
    REQUIRE(fx->unfurls.size() == 1);
    CHECK(fx->unfurls[0].url == "https://example.test/doc");
    CHECK(fx->unfurls[0].attachment.title == "A doc");
    CHECK(fx->unfurls[0].attachment.titleLink == "https://example.test/doc");
    CHECK(fx->unfurls[0].attachment.isLinkPreview);
    CHECK(fx->aiDefault == "generic summary");
    REQUIRE(fx->aiReplies.size() == 1);
    CHECK(fx->aiReplies[0].match == "palette");

    const auto &c2 = fx->history.at("C2");
    REQUIRE(c2.size() == 1);
    REQUIRE(c2[0].files.size() == 1);
    const File &clip = c2[0].files[0];
    CHECK(clip.subtype == "slack_audio");
    CHECK(clip.durationMs == 3000);
    CHECK(clip.isAudio());
    CHECK(clip.hasTranscript());
    CHECK(clip.transcriptPreview == "hello there");
}

TEST_CASE("DemoBackend: a sent link grows its unfurl a moment later", "[demo][backend]") {
    int              argc   = 1;
    char             arg0[] = "test";
    char            *argv[] = {arg0, nullptr};
    QCoreApplication app(argc, argv);

    QTemporaryDir dir;
    QString       err;
    auto          fx = loadFixture(writeFixture(dir, kMinimal), &err, kNow);
    REQUIRE(fx.has_value());
    DemoBackend be(*fx);

    std::vector<Event> events;
    rpl::lifetime      lt;
    be.events() | rpl::on_next([&](Event e) { events.push_back(std::move(e)); }, lt);

    be.sendMessage(
        ConversationId{"C1"}, OutgoingMessage{.rawText = "see https://example.test/doc/page-2"}
    );
    REQUIRE(waitFor(
        [&] {
            for (const auto &e : events)
                if (std::holds_alternative<EvMessageChanged>(e))
                    return true;
            return false;
        },
        3000
    ));
    const auto *changed = std::get_if<EvMessageChanged>(&events.back());
    REQUIRE(changed);
    REQUIRE(changed->msg.attachments.size() == 1);
    CHECK(changed->msg.attachments[0].title == "A doc");
    // Links nobody knows stay bare.
    events.clear();
    be.sendMessage(ConversationId{"C1"}, OutgoingMessage{.rawText = "see https://nowhere.test/x"});
    CHECK_FALSE(waitFor(
        [&] {
            for (const auto &e : events)
                if (std::holds_alternative<EvMessageChanged>(e))
                    return true;
            return false;
        },
        1400
    ));
}

// ── stand-in services ─────────────────────────────────────────────────────────

TEST_CASE("FakeServices: GIPHY-shaped JSON parses through GifSearch", "[demo][services]") {
    const std::vector<FakeServices::GifAsset> gifs = {
        {"party-confetti.gif", "Party confetti", 240, 160},
        {"big-check.gif", "Big check", 240, 160},
    };
    const auto body = FakeServices::giphyJson("http://127.0.0.1:1234", gifs);
    const auto out  = net::GifSearch::parseResponse(body);
    REQUIRE(out.size() == 2);
    CHECK(out[0].previewUrl == "http://127.0.0.1:1234/gif/party-confetti.gif");
    CHECK(out[0].postUrl == out[0].previewUrl);
    CHECK(out[0].previewSize == QSize(240, 160));
    CHECK(out[1].description == "Big check");
}

TEST_CASE("FakeServices: canned AI replies pick by request content", "[demo][services]") {
    QTemporaryDir dir;
    QString       err;
    const auto    fx = loadFixture(writeFixture(dir, kMinimal), &err, kNow);
    REQUIRE(fx.has_value());
    CHECK(
        FakeServices::cannedReply("... please summarize the PALETTE thread ...", *fx) ==
        "palette summary"
    );
    CHECK(FakeServices::cannedReply("something else", *fx) == "generic summary");

    const auto json = FakeServices::chatCompletionJson("hello **world**");
    const auto r    = LlmWire::parseChat(LlmWire::Format::OpenAiChat, 200, json);
    CHECK(r.ok);
    CHECK(r.response.text == "hello **world**");
}

TEST_CASE("FakeServices: serves gifs and completions over HTTP", "[demo][services]") {
    int              argc   = 1;
    char             arg0[] = "test";
    char            *argv[] = {arg0, nullptr};
    QCoreApplication app(argc, argv);

    QTemporaryDir dir;
    QString       err;
    const auto    fx = loadFixture(writeFixture(dir, kMinimal), &err, kNow);
    REQUIRE(fx.has_value());
    FakeServices services(*fx);
    REQUIRE(services.start(&err));
    CHECK(services.baseUrl().startsWith("http://127.0.0.1:"));
    CHECK(servicesBaseUrl() == services.baseUrl());

    QNetworkAccessManager nam;
    auto                  fetch = [&](const QString &path, const QByteArray &post = {}) {
        QNetworkRequest req(QUrl(services.baseUrl() + path));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QNetworkReply *reply = post.isEmpty() ? nam.get(req) : nam.post(req, post);
        REQUIRE(waitFor([&] { return reply->isFinished(); }, 3000));
        const int  status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QByteArray body = reply->readAll();
        reply->deleteLater();
        return std::make_pair(status, body);
    };
    auto [s1, models] = fetch("/v1/models");
    CHECK(s1 == 200);
    CHECK(
        LlmWire::parseModels(LlmWire::Format::OpenAiChat, s1, models).models ==
        QStringList{"lumen-1"}
    );
    auto [s2, chat] = fetch(
        "/v1/chat/completions", R"({"messages":[{"role":"user","content":"palette please"}]})"
    );
    CHECK(s2 == 200);
    CHECK(
        LlmWire::parseChat(LlmWire::Format::OpenAiChat, s2, chat).response.text == "palette summary"
    );
    auto [s3, gifs] = fetch("/v1/gifs/search?q=party");
    CHECK(s3 == 200);
    CHECK(gifs.contains("\"data\""));
    auto [s4, missing] = fetch("/gif/nope.gif");
    CHECK(s4 == 404);
}

TEST_CASE("parseTour: the phase-3 verbs", "[demo][tour]") {
    QString    err;
    const auto t = parseTour(
        R"({"steps": [
        {"key": "Return"},
        {"messageMenu": "hello"}, {"channelMenu": "C1"}, {"menuHover": "Star"}, {"menuPick": "Reply in thread"}, {"closeMenu": true},
        {"moveToThread": ["a", "b"]}, {"dialogButton": "Move"}, {"closeDialog": true},
        {"gif": "party"}, {"play": "Voice"}, {"openImage": "Week"}, {"closeImage": true},
        {"settings": {"pages": ["appearance", "ai"], "each": 900}},
        {"settings": 1200}
      ]})",
        &err
    );
    REQUIRE(t.has_value());
    CHECK(err.isEmpty());
    using K = TourStep::Kind;
    REQUIRE(t->steps.size() == 15);
    CHECK(t->steps[0].kind == K::Key);
    CHECK(t->steps[6].kind == K::MoveToThread);
    CHECK(t->steps[6].arg2 == "b");
    CHECK(t->steps[13].kind == K::Settings);
    CHECK(t->steps[13].list == QStringList{"appearance", "ai"});
    CHECK(t->steps[13].ms == 900);
    CHECK(t->steps[14].list == QStringList{"appearance"});
    CHECK(t->steps[14].ms == 1200);

    CHECK_FALSE(parseTour(R"({"steps": [{"key": "F13"}]})", &err).has_value());
    CHECK(err.contains("key is one of"));
    CHECK_FALSE(
        parseTour(R"({"steps": [{"settings": {"pages": ["plugins"]}}]})", &err).has_value()
    );
    CHECK(err.contains("unknown settings page"));
}
