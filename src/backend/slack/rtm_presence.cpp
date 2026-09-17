// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "backend/slack/rtm_presence.h"

#include "backend/slack/web_api_client.h"

#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QPointer>
#include <QUrlQuery>
#include <QWebSocket>

namespace slack {

namespace {
// A connection that lasted this long counts as durable: the backoff resets so
// the next drop retries quickly. A socket Slack drops seconds after connect keeps
// the exponential backoff instead (rtm.connect is Tier 1: a 1-2 s retry loop
// would 429 within a minute).
constexpr qint64 kStableMs       = 30'000;
// Misses before a silent socket is declared dead. Slack pongs every RTM ping, so
// two unanswered ones (a minute at the default cadence) is a real signal — it is
// also what catches a laptop-sleep gap: the half-open socket "sends" fine and
// never hears back.
constexpr int    kMaxMissedPongs = 2;

// rtm.connect errors that mean "this token will never get a socket": retrying
// would only churn the rate limit. Anything else (ratelimited, transport, an
// internal_error) is transient and backs off.
bool isFatalConnectError(const QString &err) {
    static const QStringList fatal{
        QStringLiteral("not_allowed_token_type"),
        QStringLiteral("invalid_auth"),
        QStringLiteral("not_authed"),
        QStringLiteral("account_inactive"),
        QStringLiteral("token_revoked"),
        QStringLiteral("token_expired"),
        QStringLiteral("missing_scope"),
        QStringLiteral("user_is_restricted"),
        QStringLiteral("enterprise_is_restricted"),
    };
    return fatal.contains(err);
}
} // namespace

RtmPresence::RtmPresence(WebApiClient *api, QString cookie, QObject *parent)
    : QObject(parent), _api(api), _cookie(std::move(cookie)) {
    _pingTimer.setTimerType(Qt::CoarseTimer);
    connect(&_pingTimer, &QTimer::timeout, this, &RtmPresence::sendPing);
    _tickleTimer.setTimerType(Qt::CoarseTimer);
    connect(&_tickleTimer, &QTimer::timeout, this, [this] { sendTickle(/*force=*/true); });
    _idleTimer.setSingleShot(true);
    _idleTimer.setTimerType(Qt::CoarseTimer);
    connect(&_idleTimer, &QTimer::timeout, this, &RtmPresence::onIdle);
    _reconnectTimer.setSingleShot(true);
    connect(&_reconnectTimer, &QTimer::timeout, this, [this] {
        _reconnectPending = false;
        ensureHolding();
    });
}

RtmPresence::~RtmPresence() {
    teardownConnection();
}

bool RtmPresence::isConnectedForTest() const {
    return _ws && _ws->state() == QAbstractSocket::ConnectedState;
}

void RtmPresence::setMode(PresenceMode mode) {
    if (mode == _mode)
        return;
    _mode        = mode;
    // A deliberate change is a fresh start: forget a previous refusal (the user
    // may have re-imported the session) and any inherited backoff.
    _unavailable = false;
    _reconnectMs = _t.reconnectMinMs;
    if (!holdingMode()) {
        teardownConnection();
        _idleTimer.stop();
        setState(PresenceLinkState::Off);
        return;
    }
    if (_mode == PresenceMode::WhileUsing)
        _idleTimer.start(_t.idleMs); // the click that chose this counts as activity
    else
        _idleTimer.stop();
    // Switching Idle → WhileRunning must bring the link straight back.
    if (_state == PresenceLinkState::Idle || _state == PresenceLinkState::Off)
        setState(PresenceLinkState::Connecting);
    if (isConnectedForTest()) {
        // Already up — only the tickle cadence differs between the two modes.
        if (_mode == PresenceMode::WhileRunning)
            _tickleTimer.start(_t.alwaysTickleMs);
        else
            _tickleTimer.stop();
        return;
    }
    ensureHolding();
}

void RtmPresence::noteActivity() {
    if (!holdingMode())
        return;
    if (_mode == PresenceMode::WhileUsing) {
        _idleTimer.start(_t.idleMs);
        if (_state == PresenceLinkState::Idle) {
            _reconnectMs = _t.reconnectMinMs; // the user is back: no inherited backoff
            setState(PresenceLinkState::Connecting);
            ensureHolding();
            return;
        }
    }
    sendTickle(/*force=*/false);
}

void RtmPresence::ensureHolding() {
    if (!holdingMode() || _unavailable || _connecting || _reconnectPending)
        return;
    if (_state == PresenceLinkState::Idle)
        return; // dropped on purpose; only noteActivity() brings it back
    if (isConnectedForTest())
        return;
    openAndConnect();
}

void RtmPresence::openAndConnect() {
    if (_connecting)
        return;
    _connecting = true;
    setState(PresenceLinkState::Connecting);

    // presence_sub=true keeps Slack from streaming presence_change for the whole
    // roster (we subscribe to nobody); batch_presence_aware is its prerequisite.
    QUrlQuery params;
    params.addQueryItem(QStringLiteral("batch_presence_aware"), QStringLiteral("1"));
    params.addQueryItem(QStringLiteral("presence_sub"), QStringLiteral("true"));
    const int             gen = _generation;
    QPointer<RtmPresence> self(this);
    _api->call(
        QStringLiteral("rtm.connect"),
        params,
        [self, gen](QJsonObject resp) {
            if (!self || gen != self->_generation)
                return; // torn down meanwhile — never open a competing socket
            const QString url = resp.value(QStringLiteral("url")).toString();
            if (url.isEmpty()) {
                self->_connecting = false;
                self->scheduleReconnect();
                return;
            }
            self->connectWs(QUrl(url));
        },
        [self, gen](QString err) {
            if (!self || gen != self->_generation)
                return;
            self->_connecting = false;
            if (isFatalConnectError(err)) {
                qWarning().noquote() << "RtmPresence: rtm.connect refused (" << err
                                     << ") — cannot keep this workspace active";
                self->_unavailable = true;
                self->setState(PresenceLinkState::Unavailable);
                return;
            }
            qInfo().noquote() << "RtmPresence: rtm.connect failed —" << err;
            self->scheduleReconnect();
        },
        /*quietErrors=*/true
    );
}

void RtmPresence::connectWs(const QUrl &url) {
    if (_ws) { // defensive: never overlap sockets — each one counts as a client
        _ws->disconnect(this);
        _ws->abort();
        _ws->deleteLater();
        _ws = nullptr;
    }
    _ws = new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, this);
    connect(_ws, &QWebSocket::connected, this, &RtmPresence::onConnected);
    connect(_ws, &QWebSocket::disconnected, this, &RtmPresence::onDisconnected);
    connect(_ws, &QWebSocket::textMessageReceived, this, &RtmPresence::onTextMessage);
    // QWebSocket emits no `disconnected` for a socket that never connected, so a
    // failed handshake surfaces only here.
    connect(_ws, &QWebSocket::errorOccurred, this, [this](QAbstractSocket::SocketError) {
        if (_ws && _ws->state() != QAbstractSocket::ConnectedState)
            onDisconnected();
    });
    // The URL carries no auth — the `d` cookie on the handshake IS the auth.
    QNetworkRequest req(url);
    req.setRawHeader(QByteArrayLiteral("Cookie"), QByteArrayLiteral("d=") + _cookie.toUtf8());
    _ws->open(req);
}

void RtmPresence::teardownConnection() {
    ++_generation;
    _connecting       = false;
    _reconnectPending = false;
    _connectedSinceMs = 0;
    _awaitingPongs    = 0;
    _reconnectTimer.stop();
    _pingTimer.stop();
    _tickleTimer.stop();
    if (_ws) {
        _ws->disconnect(this); // detach slots before teardown so they can't re-enter
        _ws->abort();
        _ws->deleteLater();
        _ws = nullptr;
    }
}

void RtmPresence::scheduleReconnect() {
    if (!holdingMode() || _unavailable || _reconnectPending)
        return; // coalesce: one pending reconnect at a time
    setState(PresenceLinkState::Connecting);
    const int delay   = std::max(_reconnectMs, _t.reconnectMinMs);
    _reconnectMs      = std::min(delay * 2, _t.reconnectMaxMs);
    _reconnectPending = true;
    _reconnectTimer.start(delay);
}

void RtmPresence::onConnected() {
    _connecting       = false;
    _connectedSinceMs = QDateTime::currentMSecsSinceEpoch();
    _awaitingPongs    = 0;
    _pingTimer.start(_t.pingMs);
    // Active is declared on `hello` — the handshake alone also succeeds for an
    // unauthenticated socket (Slack then sends an error frame and drops it).
}

void RtmPresence::onDisconnected() {
    _connecting = false;
    _pingTimer.stop();
    _tickleTimer.stop();
    const qint64 now = QDateTime::currentMSecsSinceEpoch();
    if (_ws) {
        qInfo().noquote() << "RtmPresence: socket closed — code" << _ws->closeCode() << "reason"
                          << _ws->closeReason() << "(up"
                          << (_connectedSinceMs ? now - _connectedSinceMs : 0) << "ms)";
        _ws->disconnect(this);
        _ws->deleteLater();
        _ws = nullptr;
    }
    const bool durable = _connectedSinceMs && (now - _connectedSinceMs) >= kStableMs;
    if (durable)
        _reconnectMs = _t.reconnectMinMs;
    _connectedSinceMs = 0;
    _awaitingPongs    = 0;
    if (holdingMode() && _state != PresenceLinkState::Idle)
        scheduleReconnect();
}

void RtmPresence::onTextMessage(const QString &text) {
    const auto    frame = QJsonDocument::fromJson(text.toUtf8()).object();
    const QString type  = frame.value(QStringLiteral("type")).toString();
    if (type == QLatin1String("hello")) {
        _reconnectMs = _t.reconnectMinMs;
        setState(PresenceLinkState::Active);
        if (_mode == PresenceMode::WhileRunning)
            _tickleTimer.start(_t.alwaysTickleMs);
        // Register as active right away rather than waiting for the first input.
        sendTickle(/*force=*/true);
        return;
    }
    if (type == QLatin1String("pong")) {
        _awaitingPongs = 0;
        return;
    }
    if (type == QLatin1String("error")) {
        // e.g. invalid_auth when the handshake lacked the cookie: Slack drops the
        // socket a few seconds later anyway; don't wait for it.
        qWarning().noquote() << "RtmPresence: server error frame —" << text.left(200);
        teardownConnection();
        scheduleReconnect();
        return;
    }
    // Everything else is the event stream (messages, typing, …) — not our job.
}

void RtmPresence::sendJson(const QString &json) {
    if (isConnectedForTest())
        _ws->sendTextMessage(json);
}

void RtmPresence::sendPing() {
    if (!isConnectedForTest())
        return;
    if (_awaitingPongs >= kMaxMissedPongs) {
        qWarning().noquote() << "RtmPresence: no pong for" << _awaitingPongs
                             << "pings — reconnecting";
        teardownConnection();
        scheduleReconnect();
        return;
    }
    ++_awaitingPongs;
    sendJson(QStringLiteral("{\"type\":\"ping\",\"id\":%1}").arg(++_pingId));
}

void RtmPresence::sendTickle(bool force) {
    if (_state != PresenceLinkState::Active || !isConnectedForTest())
        return;
    const qint64 now = QDateTime::currentMSecsSinceEpoch();
    if (!force && now - _lastTickleMs < _t.tickleGapMs)
        return;
    _lastTickleMs = now;
    ++_ticklesSent;
    sendJson(QStringLiteral("{\"type\":\"tickle\"}"));
}

void RtmPresence::onIdle() {
    if (_mode != PresenceMode::WhileUsing)
        return;
    qInfo().noquote() << "RtmPresence: no input for" << _t.idleMs / 1000
                      << "s — dropping the presence link";
    teardownConnection();
    setState(PresenceLinkState::Idle);
}

void RtmPresence::setState(PresenceLinkState s) {
    if (s == _state)
        return;
    _state = s;
    emit stateChanged(s);
}

} // namespace slack
