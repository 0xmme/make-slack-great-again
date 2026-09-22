// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
// DemoBackend — the FakeBackend populated from a demo::Fixture and made
// interactive: sends land (and get canned replies), reactions/edits/deletes/pins
// round-trip through events, threads and search work over the fixture data.
// Compiled only with MSGA_DEMO (Debug builds) — never part of a release.
#pragma once

#include "backend/demo/demo_fixture.h"
#include "backend/fake_backend/fake_backend.h"

#include <QObject>
#include <deque>

namespace demo {

class DemoBackend : public FakeBackend {
public:
    explicit DemoBackend(Fixture fx);

    Capabilities capabilities() const override;

    rpl::producer<UserId>                    loadMe() override;
    rpl::producer<std::vector<Conversation>> loadConversations() override;
    rpl::producer<std::vector<User>>         loadUsers() override;
    rpl::producer<MessagePage>  loadHistory(ConversationId, std::optional<QString>) override;
    rpl::producer<bool>         loadPresence(UserId) override;
    rpl::producer<User>         loadUser(UserId) override;
    rpl::producer<Conversation> loadConversationInfo(ConversationId, bool background) override;
    rpl::producer<MessagePage> loadThread(ConversationId, Ts root, std::optional<QString>) override;
    rpl::producer<Message>     loadMessageAt(ConversationId, Ts) override;
    rpl::producer<std::vector<ConversationId>> loadStarredConversations() override;
    rpl::producer<std::vector<SearchResult>>   searchMessages(const QString &) override;
    // The Threads overview: every fixture thread the signed-in user took part
    // in, newest activity first, with the read cursor markThreadRead() moved.
    rpl::producer<ThreadsViewPage>             loadThreadsView(const QString &cursor) override;
    void markThreadRead(ConversationId, Ts root, Ts ts) override;
    // Saved messages ("Save for later" / reminders): an in-memory list.
    rpl::producer<std::vector<MessageReminder>> loadMessageReminders() override;
    void                                        setMessageReminder(
        ConversationId, Ts, qint64 dueAt, std::function<void(bool ok, QString err)> done = {}
    ) override;
    void removeMessageReminder(
        ConversationId, Ts, std::function<void(bool ok, QString err)> done = {}
    ) override;

    void sendMessage(
        ConversationId, OutgoingMessage, std::function<void(bool ok, QString err)> done = {}
    ) override;
    void editMessage(ConversationId, Ts, OutgoingMessage) override;
    void deleteMessage(ConversationId, Ts) override;
    void addReaction(ConversationId, Ts, QString) override;
    void removeReaction(ConversationId, Ts, QString) override;
    void pinMessage(ConversationId, Ts) override;
    void unpinMessage(ConversationId, Ts) override;
    void starConversation(ConversationId, bool star) override;
    void uploadFiles(
        ConversationId,
        const QStringList &,
        const QString &,
        std::optional<Ts>                       = std::nullopt,
        std::function<void(bool, QString)> done = {}
    ) override;
    void downloadFile(
        const QString &, std::function<void(QByteArray)>, std::function<void(QString)> = {}
    ) override;

    // Post a message as another fixture user right now (tour scripts / tests).
    // Returns the ts it got.
    Ts postAs(ConversationId, UserId, const QString &mrkdwn, std::optional<Ts> threadRoot = {});
    // The ts of the first message in `conv` (top-level or reply) whose text
    // contains `fragment`, case-insensitively — how tour scripts name messages.
    std::optional<Ts> findTs(const ConversationId &conv, const QString &fragment) const;

    const Fixture &fixture() const { return _fx; }

private:
    // Every read completes on a later event-loop turn, like a network backend:
    // callers connect to "loaded" signals AFTER subscribing, and a synchronous
    // producer would fire before they do (the composer never appeared).
    template <typename T>
    rpl::producer<T> later(T value, int delayMs = kReadLatencyMs);
    template <typename T>
    rpl::producer<T>     maybeLater(std::optional<T> value);
    static constexpr int kReadLatencyMs = 25;

    Ts       nextTs();
    Message *findMessage(const ConversationId &conv, const Ts &ts);
    Message  makeMessage(UserId author, const QString &mrkdwn, std::optional<Ts> threadRoot);
    void     appendMessage(const ConversationId &conv, Message msg);
    void     scheduleAutoReply(const ConversationId &conv, std::optional<Ts> threadRoot);
    // Slack-style unfurl: ~1 s after a message with a known link (fixture
    // `unfurls`, or a GIF served by the demo services) lands, attach its preview
    // and fire EvMessageChanged.
    void     scheduleUnfurl(const ConversationId &conv, const Message &msg);
    std::vector<Attachment> unfurlsFor(const QString &rawText) const;
    void updateConversation(const ConversationId &id, const std::function<void(Conversation &)> &);

    Fixture                                           _fx;
    std::unordered_map<QString, std::vector<Message>> _threads;    // threadKey → replies
    std::unordered_map<QString, Ts>                   _threadRead; // threadKey → read cursor
    std::vector<MessageReminder>                      _saved;
    std::deque<AutoReply>                             _autoReplies;
    qint64                                            _lastUsec  = 0;
    int                                               _fileIndex = 1000;
    QObject                                           _timerGuard; // scopes the reply timers
};

} // namespace demo
