// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
// Local stand-ins for the network services the demo shows off: a GIPHY-shaped
// search API serving the fixture's GIFs, and an OpenAI-compatible chat endpoint
// answering with canned text from the fixture. One tiny HTTP/1.1 server on
// 127.0.0.1, alive for the process. Compiled only with MSGA_DEMO.
#pragma once

#include "backend/demo/demo_fixture.h"

#include <QByteArray>
#include <QObject>
#include <QString>
#include <QTcpServer>
#include <vector>

class QTcpSocket;

namespace demo {

class FakeServices : public QObject {
public:
    struct GifAsset {
        QString file; // name inside <fixture>/assets/gifs
        QString title;
        int     width  = 0;
        int     height = 0;
    };

    explicit FakeServices(const Fixture &fx, QObject *parent = nullptr);

    bool    start(QString *error);
    QString baseUrl() const { return _baseUrl; } // "http://127.0.0.1:PORT"

    // Pure builders — what the routes answer with (tests exercise these).
    static QByteArray giphyJson(const QString &baseUrl, const std::vector<GifAsset> &gifs);
    static QByteArray chatCompletionJson(const QString &text);
    // The canned AI answer for a request body: the first fixture reply whose
    // `match` occurs in the body (case-insensitive), else the default.
    static QString    cannedReply(const QByteArray &requestBody, const Fixture &fx);

    static std::vector<GifAsset> scanGifs(const QString &fixtureDir);

private:
    void handle(QTcpSocket *sock, const QByteArray &request);
    void reply(QTcpSocket *sock, int status, const QByteArray &type, const QByteArray &body);

    Fixture               _fx;
    std::vector<GifAsset> _gifs;
    QTcpServer            _server;
    QString               _baseUrl;
};

// Base URL of the running stand-in server (empty when demo services are off).
// DemoBackend uses it to recognise GIF links it should unfurl.
QString servicesBaseUrl();
void    setServicesBaseUrl(const QString &url);

} // namespace demo
