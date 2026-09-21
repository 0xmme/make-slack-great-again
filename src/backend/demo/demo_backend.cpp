// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "demo_backend.h"

#include "backend/demo/demo_services.h"
#include "text/mrkdwn_parser.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QImageReader>
#include <QRegularExpression>
#include <QTimer>
#include <QUrl>
#include <algorithm>

namespace demo {

namespace {

// Slack's chat.postMessage round trip, roughly: long enough that the
// translucent optimistic copy is visible, short enough not to look stuck.
constexpr int kSendConfirmMs = 180;

} // namespace

DemoBackend::DemoBackend(Fixture fx) : _fx(std::move(fx)) {
    _conversations = _fx.conversations;
    _users         = _fx.users;
    _history       = _fx.history;
    _threads       = _fx.threads;
    _autoReplies.assign(_fx.autoReplies.begin(), _fx.autoReplies.end());
    for (const auto &c : _fx.conversations)
        _convInfo[c.id.value] = c;
}

Capabilities DemoBackend::capabilities() const {
    Capabilities c;
    c.typing        = true;
    c.presence      = true;
    c.livePresence  = true;
    c.reactions     = true;
    c.editMessage   = true;
    c.deleteMessage = true;
    c.threads       = true;
    c.fileUpload    = true;
    c.moveToThread  = true;
    c.slashCommands = true;
    return c;
}

// ── reads ─────────────────────────────────────────────────────────────────────

template <typename T>
rpl::producer<T> DemoBackend::later(T value, int delayMs) {
    return [guard = &_timerGuard, value = std::move(value), delayMs](auto consumer) mutable {
        QTimer::singleShot(delayMs, guard, [consumer, value = std::move(value)]() mutable {
            consumer.put_next(std::move(value));
            consumer.put_done();
        });
        return rpl::lifetime();
    };
}

template <typename T>
rpl::producer<T> DemoBackend::maybeLater(std::optional<T> value) {
    return [guard = &_timerGuard, value = std::move(value)](auto consumer) mutable {
        QTimer::singleShot(kReadLatencyMs, guard, [consumer, value = std::move(value)]() mutable {
            if (value)
                consumer.put_next(std::move(*value));
            consumer.put_done();
        });
        return rpl::lifetime();
    };
}

rpl::producer<UserId> DemoBackend::loadMe() {
    return later(_fx.me);
}

rpl::producer<std::vector<Conversation>> DemoBackend::loadConversations() {
    return later(_conversations.current());
}

rpl::producer<std::vector<User>> DemoBackend::loadUsers() {
    return later(_users.current());
}

rpl::producer<MessagePage> DemoBackend::loadHistory(ConversationId conv, std::optional<QString>) {
    MessagePage page;
    if (const auto it = _history.find(conv.value); it != _history.end())
        page.messages = it->second;
    return later(std::move(page), kReadLatencyMs * 2);
}

rpl::producer<bool> DemoBackend::loadPresence(UserId id) {
    bool active = false;
    for (const auto &u : _users.current())
        if (u.id == id)
            active = u.isActive;
    return later(active);
}

rpl::producer<User> DemoBackend::loadUser(UserId id) {
    std::optional<User> found;
    for (const auto &u : _users.current())
        if (u.id == id)
            found = u;
    return maybeLater(std::move(found));
}

rpl::producer<Conversation> DemoBackend::loadConversationInfo(ConversationId id, bool) {
    std::optional<Conversation> found;
    for (const auto &c : _conversations.current())
        if (c.id == id)
            found = c;
    return maybeLater(std::move(found));
}

rpl::producer<MessagePage>
DemoBackend::loadThread(ConversationId conv, Ts root, std::optional<QString>) {
    // conversations.replies shape: the root first, then the replies oldest-first.
    MessagePage page;
    if (const Message *r = findMessage(conv, root))
        page.messages.push_back(*r);
    if (const auto it = _threads.find(Fixture::threadKey(conv, root)); it != _threads.end())
        page.messages.insert(page.messages.end(), it->second.begin(), it->second.end());
    return later(std::move(page), kReadLatencyMs * 2);
}

rpl::producer<Message> DemoBackend::loadMessageAt(ConversationId conv, Ts ts) {
    std::optional<Message> found;
    if (const Message *m = findMessage(conv, ts))
        found = *m;
    return maybeLater(std::move(found));
}

rpl::producer<std::vector<ConversationId>> DemoBackend::loadStarredConversations() {
    std::vector<ConversationId> out;
    for (const auto &c : _conversations.current())
        if (c.isStarred)
            out.push_back(c.id);
    return later(std::move(out));
}

rpl::producer<std::vector<SearchResult>> DemoBackend::searchMessages(const QString &query) {
    std::vector<SearchResult> out;
    const QString             q = query.trimmed();
    if (!q.isEmpty()) {
        auto scan = [&](const ConversationId &conv, const std::vector<Message> &msgs) {
            QString name;
            for (const auto &c : _conversations.current())
                if (c.id == conv)
                    name = c.name;
            for (const auto &m : msgs)
                if (m.text.text.contains(q, Qt::CaseInsensitive))
                    out.push_back(SearchResult{conv, name, m});
        };
        for (const auto &[conv, msgs] : _history)
            scan(ConversationId{conv}, msgs);
        for (const auto &[key, replies] : _threads)
            scan(ConversationId{key.left(key.indexOf(QLatin1Char('/')))}, replies);
        std::sort(out.begin(), out.end(), [](const SearchResult &a, const SearchResult &b) {
            return a.msg.date > b.msg.date; // newest first, like search.messages
        });
    }
    return later(std::move(out), kReadLatencyMs * 4);
}

// ── writes ────────────────────────────────────────────────────────────────────

void DemoBackend::sendMessage(
    ConversationId conv, OutgoingMessage out, std::function<void(bool ok, QString err)> done
) {
    Message  msg = makeMessage(_fx.me, out.rawText, out.threadRoot);
    const Ts ts  = msg.ts;
    // Confirm asynchronously: Session is still inside postMessage() when this is
    // called, and a real server never answers synchronously either.
    QTimer::singleShot(kSendConfirmMs, &_timerGuard, [this, conv, msg, done, out] {
        appendMessage(conv, msg);
        if (done)
            done(true, {});
        scheduleAutoReply(conv, out.threadRoot);
    });
    Q_UNUSED(ts);
}

void DemoBackend::editMessage(ConversationId conv, Ts ts, TextWithEntities text) {
    Message *m = findMessage(conv, ts);
    if (!m)
        return;
    m->text    = text;
    m->edited  = true;
    // The composer hands us the parsed text; keep rawText in step for re-edits.
    m->rawText = text.text;
    _events.fire(EvMessageChanged{conv, *m, /*textOnly=*/true});
}

void DemoBackend::deleteMessage(ConversationId conv, Ts ts) {
    std::optional<Ts> root;
    if (const Message *m = findMessage(conv, ts))
        root = m->threadRoot;
    if (root) {
        auto &replies = _threads[Fixture::threadKey(conv, *root)];
        std::erase_if(replies, [&](const Message &m) { return m.ts == ts; });
        if (Message *r = findMessage(conv, *root)) {
            r->replyCount = int(replies.size());
            _events.fire(EvMessageChanged{conv, *r});
        }
    } else {
        auto &msgs = _history[conv.value];
        std::erase_if(msgs, [&](const Message &m) { return m.ts == ts; });
        _threads.erase(Fixture::threadKey(conv, ts));
    }
    _events.fire(EvMessageDeleted{conv, ts, root});
}

void DemoBackend::addReaction(ConversationId conv, Ts ts, QString name) {
    Message *m = findMessage(conv, ts);
    if (!m)
        return;
    auto it = std::find_if(m->reactions.begin(), m->reactions.end(), [&](const Reaction &r) {
        return r.name == name;
    });
    if (it == m->reactions.end()) {
        m->reactions.push_back(Reaction{name, 1, {_fx.me}});
    } else if (std::find(it->users.begin(), it->users.end(), _fx.me) == it->users.end()) {
        it->users.push_back(_fx.me);
        it->count = int(it->users.size());
    }
    _events.fire(EvReactionAdded{conv, ts, name, _fx.me});
}

void DemoBackend::removeReaction(ConversationId conv, Ts ts, QString name) {
    Message *m = findMessage(conv, ts);
    if (!m)
        return;
    for (auto it = m->reactions.begin(); it != m->reactions.end(); ++it) {
        if (it->name != name)
            continue;
        std::erase(it->users, _fx.me);
        it->count = int(it->users.size());
        if (it->count == 0)
            m->reactions.erase(it);
        break;
    }
    _events.fire(EvReactionRemoved{conv, ts, name, _fx.me});
}

void DemoBackend::pinMessage(ConversationId conv, Ts ts) {
    if (Message *m = findMessage(conv, ts)) {
        m->pinned   = true;
        m->pinnedBy = _fx.me;
        _events.fire(EvMessageChanged{conv, *m});
    }
}

void DemoBackend::unpinMessage(ConversationId conv, Ts ts) {
    if (Message *m = findMessage(conv, ts)) {
        m->pinned   = false;
        m->pinnedBy = {};
        _events.fire(EvMessageChanged{conv, *m});
    }
}

void DemoBackend::starConversation(ConversationId id, bool star) {
    updateConversation(id, [star](Conversation &c) { c.isStarred = star; });
}

void DemoBackend::uploadFiles(
    ConversationId                     conv,
    const QStringList                 &paths,
    const QString                     &comment,
    std::optional<Ts>                  threadRoot,
    std::function<void(bool, QString)> done
) {
    Message msg = makeMessage(_fx.me, comment, threadRoot);
    for (const auto &p : paths)
        msg.files.push_back(fileFromLocalPath(p, ++_fileIndex));
    QTimer::singleShot(kSendConfirmMs * 3, &_timerGuard, [this, conv, msg, done] {
        appendMessage(conv, msg);
        if (done)
            done(true, {});
    });
}

void DemoBackend::downloadFile(
    const QString &url, std::function<void(QByteArray)> onData, std::function<void(QString)> onError
) {
    QFile f(QUrl(url).toLocalFile());
    if (!f.open(QIODevice::ReadOnly)) {
        if (onError)
            onError(QStringLiteral("demo: cannot read %1").arg(url));
        return;
    }
    if (onData)
        onData(f.readAll());
}

Ts DemoBackend::postAs(
    ConversationId conv, UserId user, const QString &mrkdwn, std::optional<Ts> threadRoot
) {
    Message  msg = makeMessage(user, mrkdwn, threadRoot);
    const Ts ts  = msg.ts;
    appendMessage(conv, std::move(msg));
    return ts;
}

// ── internals ─────────────────────────────────────────────────────────────────

Ts DemoBackend::nextTs() {
    qint64 usec = QDateTime::currentMSecsSinceEpoch() * 1000;
    if (usec <= _lastUsec)
        usec = _lastUsec + 1;
    _lastUsec = usec;
    return QStringLiteral("%1.%2").arg(usec / 1000000).arg(usec % 1000000, 6, 10, QLatin1Char('0'));
}

Message *DemoBackend::findMessage(const ConversationId &conv, const Ts &ts) {
    if (const auto it = _history.find(conv.value); it != _history.end())
        for (auto &m : it->second)
            if (m.ts == ts)
                return &m;
    const QString prefix = conv.value + QLatin1Char('/');
    for (auto &[key, replies] : _threads) {
        if (!key.startsWith(prefix))
            continue;
        for (auto &m : replies)
            if (m.ts == ts)
                return &m;
    }
    return nullptr;
}

Message DemoBackend::makeMessage(UserId author, const QString &mrkdwn, std::optional<Ts> root) {
    Message m;
    m.ts         = nextTs();
    m.date       = decimalTsToMicros(m.ts);
    m.author     = std::move(author);
    m.rawText    = mrkdwn;
    m.text       = MrkdwnParser::parse(mrkdwn);
    m.threadRoot = std::move(root);
    return m;
}

void DemoBackend::appendMessage(const ConversationId &conv, Message msg) {
    if (msg.threadRoot) {
        Message *root = findMessage(conv, *msg.threadRoot);
        if (!root)
            return;
        msg.parentUserId = root->author;
        auto &replies    = _threads[Fixture::threadKey(conv, *msg.threadRoot)];
        replies.push_back(msg);
        root->replyCount  = int(replies.size());
        root->latestReply = msg.ts;
        if (std::find(root->replyUsers.begin(), root->replyUsers.end(), msg.author) ==
                root->replyUsers.end() &&
            root->replyUsers.size() < 5)
            root->replyUsers.push_back(msg.author);
        const Message rootCopy = *root;
        _events.fire(EvMessageNew{conv, msg});
        _events.fire(EvMessageChanged{conv, rootCopy});
        scheduleUnfurl(conv, msg);
        return;
    }
    _history[conv.value].push_back(msg);
    updateConversation(conv, [&](Conversation &c) { c.latestTs = msg.ts; });
    _events.fire(EvMessageNew{conv, msg});
    scheduleUnfurl(conv, msg);
}

std::vector<Attachment> DemoBackend::unfurlsFor(const QString &rawText) const {
    std::vector<Attachment>         out;
    static const QRegularExpression urlRe(R"(https?://[^\s<>|]+)");
    auto                            it = urlRe.globalMatch(rawText);
    while (it.hasNext()) {
        const QString url   = it.next().captured(0);
        bool          found = false;
        for (const auto &u : _fx.unfurls) {
            if (url.startsWith(u.url)) {
                out.push_back(u.attachment);
                found = true;
                break;
            }
        }
        if (found)
            continue;
        // A GIF from the stand-in GIPHY: unfurl it as the animated image card.
        const QString base = servicesBaseUrl();
        if (!base.isEmpty() && url.startsWith(base + QLatin1String("/gif/"))) {
            const QString file = QUrl(url).fileName();
            const QSize   sz   = QImageReader(QDir(_fx.dir).filePath("assets/gifs/" + file)).size();
            Attachment    a;
            a.imageUrl      = url;
            a.imageWidth    = sz.width();
            a.imageHeight   = sz.height();
            a.isLinkPreview = true;
            a.fallback      = file;
            out.push_back(std::move(a));
        }
    }
    return out;
}

void DemoBackend::scheduleUnfurl(const ConversationId &conv, const Message &msg) {
    auto atts = unfurlsFor(msg.rawText);
    if (atts.empty())
        return;
    QTimer::singleShot(900, &_timerGuard, [this, conv, ts = msg.ts, atts = std::move(atts)] {
        Message *m = findMessage(conv, ts);
        if (!m)
            return;
        m->attachments.insert(m->attachments.end(), atts.begin(), atts.end());
        _events.fire(EvMessageChanged{conv, *m});
    });
}

void DemoBackend::scheduleAutoReply(const ConversationId &conv, std::optional<Ts> threadRoot) {
    auto it = std::find_if(_autoReplies.begin(), _autoReplies.end(), [&](const AutoReply &r) {
        return r.conv == conv.value;
    });
    if (it == _autoReplies.end())
        return;
    const AutoReply reply = *it;
    _autoReplies.erase(it);

    const int typingMs = std::max(0, reply.typingMs);
    QTimer::singleShot(reply.afterMs, &_timerGuard, [this, conv, reply, threadRoot, typingMs] {
        if (typingMs > 0)
            _events.fire(EvTyping{conv, reply.user});
        QTimer::singleShot(typingMs, &_timerGuard, [this, conv, reply, threadRoot] {
            postAs(conv, reply.user, reply.text, threadRoot);
        });
    });
}

void DemoBackend::updateConversation(
    const ConversationId &id, const std::function<void(Conversation &)> &fn
) {
    auto convs = _conversations.current();
    for (auto &c : convs)
        if (c.id == id)
            fn(c);
    _conversations = std::move(convs);
    for (const auto &c : _conversations.current())
        _convInfo[c.id.value] = c;
}

} // namespace demo
