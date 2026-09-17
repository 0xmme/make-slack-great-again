// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
// Holds an RTM WebSocket on the user's own (session, xoxc) token purely so that
// Slack counts this app as a connected client — see PresenceMode. Slack only ever
// reports a user "active" while at least one client connection exists
// (users.getPresence's `online`); the public users.setPresence can force "away"
// but never "active", so a Web-API-only client is always away to everyone unless
// an official Slack app happens to be running.
//
// rtm.connect works for a session token (NOT for a granular OAuth token), and the
// wss URL it returns carries no auth of its own: the socket handshake MUST send
// the `d` cookie, otherwise Slack answers
// {"type":"error","error":{"msg":"invalid_auth","code":401}} and drops the socket
// ~5 s later (verified live — that drop is what once shelved RTM as "unusable").
//
// Frames on this socket (message events for every conversation the user is in)
// are ignored — delivery stays with the Session's polling. Only `hello`, `pong`
// and `error` are looked at. Slack DOES answer RTM json pings with pongs (unlike
// Socket Mode), so a missing pong is a real liveness signal here. User input is
// forwarded as `tickle` frames, the official client's way of keeping the server's
// auto-away clock at bay.
#pragma once

#include "backend/domain.h"

#include <QObject>
#include <QString>
#include <QTimer>
#include <QUrl>

class QWebSocket;

namespace slack {

class WebApiClient;

class RtmPresence : public QObject {
    Q_OBJECT
public:
    // `api` performs rtm.connect (it already carries the token, the `d` cookie and
    // the per-workspace host); it must outlive this object. `cookie` is the same
    // `d` cookie, needed again on the WebSocket handshake.
    RtmPresence(WebApiClient *api, QString cookie, QObject *parent = nullptr);
    ~RtmPresence() override;

    // Native → drop the link; either holding mode → establish it (WhileUsing
    // treats the change itself as activity). Idempotent.
    void              setMode(PresenceMode mode);
    PresenceMode      mode() const { return _mode; }
    PresenceLinkState state() const { return _state; }

    // Real user input in the app. WhileUsing: re-arms the idle timer and brings an
    // idle-dropped link back. Both holding modes: sends a `tickle` (throttled).
    void noteActivity();

    // ── Test seams ──────────────────────────────────────────────────────────
    struct Timing {
        int pingMs;         // json ping cadence (Slack pongs each one)
        int tickleGapMs;    // min spacing of activity tickles
        int alwaysTickleMs; // WhileRunning: unconditional tickle cadence
        int idleMs;         // WhileUsing: drop the link after this long without input
        int reconnectMinMs; // backoff start (doubles up to reconnectMaxMs)
        int reconnectMaxMs;
    };
    void setTimingForTest(const Timing &t) { _t = t; }
    bool isConnectedForTest() const;
    int  ticklesSentForTest() const { return _ticklesSent; }

signals:
    void stateChanged(PresenceLinkState state);

private:
    bool holdingMode() const { return _mode != PresenceMode::Native; }
    // Open the link if the mode wants one and none is up or already in flight.
    void ensureHolding();
    void openAndConnect(); // rtm.connect → wss URL → connectWs
    void connectWs(const QUrl &url);
    // Abort the socket and any in-flight handshake (signals detached first so
    // their teardown can't re-enter our slots); stop the link timers. Leaves the
    // state alone — callers set the one that explains the drop.
    void teardownConnection();
    void scheduleReconnect();
    void onConnected();
    void onDisconnected();
    void onTextMessage(const QString &text);
    void sendJson(const QString &json);
    void sendPing();
    void sendTickle(bool force);
    void onIdle();
    void setState(PresenceLinkState s);

    WebApiClient     *_api;
    QString           _cookie;
    PresenceMode      _mode             = PresenceMode::Native;
    PresenceLinkState _state            = PresenceLinkState::Off;
    QWebSocket       *_ws               = nullptr;
    // Single-flight guard: an rtm.connect or socket open is underway. Further
    // connect triggers coalesce (rtm.connect is Tier 1 — ~1/min).
    bool              _connecting       = false;
    bool              _reconnectPending = false;
    // rtm.connect refused this token outright (OAuth token, revoked session…):
    // give up until the mode is changed again instead of retrying into a ratelimit.
    bool              _unavailable      = false;
    // Bumped on every teardown; an rtm.connect reply from a superseded attempt
    // (the queue can't abort it) must not open a competing socket.
    int               _generation       = 0;
    int               _reconnectMs      = 0;
    qint64            _connectedSinceMs = 0; // 0 = not connected; backoff resets only after
                                             // a durable (≥ kStableMs) connection
    int               _pingId           = 0;
    int               _awaitingPongs    = 0; // pings sent since the last pong
    qint64            _lastTickleMs     = 0;
    int               _ticklesSent      = 0;
    QTimer            _pingTimer;
    QTimer            _tickleTimer;    // WhileRunning only
    QTimer            _idleTimer;      // WhileUsing only (single-shot)
    QTimer            _reconnectTimer; // single-shot backoff
    Timing            _t{
        /*pingMs=*/30'000,
        /*tickleGapMs=*/60'000,
        /*alwaysTickleMs=*/5 * 60'000,
        /*idleMs=*/30 * 60'000,
        /*reconnectMinMs=*/2'000,
        /*reconnectMaxMs=*/60'000,
    };
};

} // namespace slack
