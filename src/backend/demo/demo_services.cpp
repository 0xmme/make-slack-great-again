// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "demo_services.h"

#include <QDir>
#include <QFile>
#include <QImageReader>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include <QUrl>
#include <QUrlQuery>

namespace demo {

namespace {
QString g_servicesBase;
} // namespace

QString servicesBaseUrl() {
    return g_servicesBase;
}
void setServicesBaseUrl(const QString &url) {
    g_servicesBase = url;
}

FakeServices::FakeServices(const Fixture &fx, QObject *parent)
    : QObject(parent), _fx(fx), _gifs(scanGifs(fx.dir)) {
    connect(&_server, &QTcpServer::newConnection, this, [this] {
        while (auto *sock = _server.nextPendingConnection()) {
            auto buffer = std::make_shared<QByteArray>();
            connect(sock, &QTcpSocket::readyRead, this, [this, sock, buffer] {
                buffer->append(sock->readAll());
                const int headerEnd = buffer->indexOf("\r\n\r\n");
                if (headerEnd < 0)
                    return;
                // Wait for the whole body before routing (POSTs carry JSON).
                int contentLength = 0;
                for (const auto &line : buffer->left(headerEnd).split('\n'))
                    if (line.toLower().startsWith("content-length:"))
                        contentLength = line.mid(15).trimmed().toInt();
                if (buffer->size() < headerEnd + 4 + contentLength)
                    return;
                handle(sock, *buffer);
                buffer->clear();
            });
            connect(sock, &QTcpSocket::disconnected, sock, &QObject::deleteLater);
        }
    });
}

bool FakeServices::start(QString *error) {
    if (!_server.listen(QHostAddress::LocalHost)) {
        if (error)
            *error = QStringLiteral("demo services: %1").arg(_server.errorString());
        return false;
    }
    _baseUrl = QStringLiteral("http://127.0.0.1:%1").arg(_server.serverPort());
    setServicesBaseUrl(_baseUrl);
    return true;
}

std::vector<FakeServices::GifAsset> FakeServices::scanGifs(const QString &fixtureDir) {
    std::vector<GifAsset> out;
    QDir                  dir(QDir(fixtureDir).filePath(QStringLiteral("assets/gifs")));
    for (const auto &name : dir.entryList({QStringLiteral("*.gif")}, QDir::Files, QDir::Name)) {
        GifAsset g;
        g.file  = name;
        g.title = QFileInfo(name).completeBaseName().replace(QLatin1Char('-'), QLatin1Char(' '));
        if (!g.title.isEmpty())
            g.title[0] = g.title[0].toUpper();
        const QSize sz = QImageReader(dir.filePath(name)).size();
        g.width        = sz.width();
        g.height       = sz.height();
        out.push_back(std::move(g));
    }
    return out;
}

QByteArray FakeServices::giphyJson(const QString &baseUrl, const std::vector<GifAsset> &gifs) {
    // The renditions GifSearch::parseResponse reads: a fixed_width preview and a
    // downsized send rendition. Both point at the same file here.
    QJsonArray data;
    int        n = 0;
    for (const auto &g : gifs) {
        const QString url = baseUrl + QStringLiteral("/gif/") + g.file;
        QJsonObject   rendition{
            {"url", url},
            {"width", QString::number(g.width)},
            {"height", QString::number(g.height)},
        };
        data.append(
            QJsonObject{
                {"id", QStringLiteral("demo%1").arg(++n)},
                {"title", g.title},
                {"alt_text", g.title},
                {"images", QJsonObject{{"fixed_width", rendition}, {"downsized", rendition}}},
            }
        );
    }
    return QJsonDocument(
               QJsonObject{{"data", data}, {"meta", QJsonObject{{"status", 200}}}}
    ).toJson(QJsonDocument::Compact);
}

QByteArray FakeServices::chatCompletionJson(const QString &text) {
    return QJsonDocument(
               QJsonObject{
                   {"id", "chatcmpl-demo"},
                   {"object", "chat.completion"},
                   {"model", "lumen-1"},
                   {"choices",
                    QJsonArray{QJsonObject{
                        {"index", 0},
                        {"finish_reason", "stop"},
                        {"message", QJsonObject{{"role", "assistant"}, {"content", text}}},
                    }}},
                   {"usage", QJsonObject{{"prompt_tokens", 0}, {"completion_tokens", 0}}},
               }
    )
        .toJson(QJsonDocument::Compact);
}

QString FakeServices::cannedReply(const QByteArray &requestBody, const Fixture &fx) {
    const QString body = QString::fromUtf8(requestBody);
    for (const auto &r : fx.aiReplies)
        if (body.contains(r.match, Qt::CaseInsensitive))
            return r.text;
    return fx.aiDefault.isEmpty() ? QStringLiteral("Nothing to add — the thread speaks for itself.")
                                  : fx.aiDefault;
}

void FakeServices::handle(QTcpSocket *sock, const QByteArray &request) {
    const int               lineEnd = request.indexOf("\r\n");
    const QByteArray        line    = request.left(lineEnd);
    const QList<QByteArray> parts   = line.split(' ');
    if (parts.size() < 2) {
        reply(sock, 400, "text/plain", "bad request");
        return;
    }
    const QByteArray method = parts[0];
    const QUrl       url(QString::fromUtf8(parts[1]));
    const QString    path   = url.path();
    const int        bodyAt = request.indexOf("\r\n\r\n") + 4;
    const QByteArray body   = request.mid(bodyAt);

    if (path.startsWith(QLatin1String("/v1/gifs/"))) {
        reply(sock, 200, "application/json", giphyJson(_baseUrl, _gifs));
    } else if (path.startsWith(QLatin1String("/gif/"))) {
        const QString name = QFileInfo(path.mid(5)).fileName(); // no traversal
        QFile         f(QDir(_fx.dir).filePath(QStringLiteral("assets/gifs/") + name));
        if (f.open(QIODevice::ReadOnly))
            reply(sock, 200, "image/gif", f.readAll());
        else
            reply(sock, 404, "text/plain", "no such gif");
    } else if (path.endsWith(QLatin1String("/models"))) {
        reply(
            sock,
            200,
            "application/json",
            R"({"object":"list","data":[{"id":"lumen-1","object":"model"}]})"
        );
    } else if (path.endsWith(QLatin1String("/chat/completions")) && method == "POST") {
        reply(sock, 200, "application/json", chatCompletionJson(cannedReply(body, _fx)));
    } else {
        reply(sock, 404, "text/plain", "not found");
    }
}

void FakeServices::reply(
    QTcpSocket *sock, int status, const QByteArray &type, const QByteArray &body
) {
    QByteArray head = "HTTP/1.1 " + QByteArray::number(status) +
                      (status == 200 ? " OK" : " Error") + "\r\nContent-Type: " + type +
                      "\r\nContent-Length: " + QByteArray::number(body.size()) +
                      "\r\nAccess-Control-Allow-Origin: *\r\nConnection: close\r\n\r\n";
    sock->write(head + body);
    sock->flush();
    sock->disconnectFromHost();
}

} // namespace demo
