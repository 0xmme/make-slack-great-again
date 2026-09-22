// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "custom_workspace_icon.h"
#include "auth/token_store.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QStandardPaths>

namespace CustomWorkspaceIcon {

QString directory() {
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
           QStringLiteral("/workspace_icons");
}

QImage prepare(const QImage &src) {
    if (src.isNull())
        return {};
    const int   side = qMin(src.width(), src.height());
    const QRect crop((src.width() - side) / 2, (src.height() - side) / 2, side, side);
    QImage      out = src.copy(crop);
    if (side > kStoredSize)
        out = out.scaled(kStoredSize, kStoredSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    // PNG keeps alpha; a format with a palette or premultiplied alpha would
    // otherwise round-trip differently through the cache decoder.
    return out.convertToFormat(QImage::Format_ARGB32);
}

// Only the handle's alphanumerics make it into the file name: the handle has
// a ':' (bad on Windows) and any future service id might carry worse.
static QString fileStem(const WorkspaceKey &key) {
    QString stem;
    for (const QChar ch : key.toString())
        stem.append(ch.isLetterOrNumber() ? ch : QLatin1Char('_'));
    return stem;
}

QString install(const WorkspaceKey &key, const QImage &src) {
    const QImage img = prepare(src);
    if (img.isNull())
        return {};
    const QString dir = directory();
    if (!QDir().mkpath(dir))
        return {};
    // The stamp only has to differ from the file currently installed (and any
    // stray leftover); two installs in one millisecond bump it.
    const QString previous = TokenStore::customWorkspaceIconPath(key);
    QString       path;
    for (qint64 stamp = QDateTime::currentMSecsSinceEpoch();; ++stamp) {
        path = QStringLiteral("%1/%2-%3.png").arg(dir, fileStem(key)).arg(stamp);
        if (path != previous && !QFile::exists(path))
            break;
    }
    if (!img.save(path, "PNG"))
        return {};
    TokenStore::setCustomWorkspaceIconPath(key, path);
    if (!previous.isEmpty() && previous != path)
        QFile::remove(previous);
    return path;
}

void remove(const WorkspaceKey &key) {
    const QString previous = TokenStore::customWorkspaceIconPath(key);
    TokenStore::setCustomWorkspaceIconPath(key, {});
    if (!previous.isEmpty())
        QFile::remove(previous);
}

} // namespace CustomWorkspaceIcon
