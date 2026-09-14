// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
// Slack's composer stores pasted-URL labels already truncated ("host/path/…/…")
// — only the Link entity keeps the full URL. These helpers detect such labels
// so display can rebuild a longer one and copy/export can substitute the full
// URL (the visible "…" text is useless on the clipboard).
#pragma once

#include "backend/domain.h"

#include <QUrl>

namespace LinkLabels {

// True for a GIPHY media asset — what the composer's GIF picker posts, and what
// anyone pasting a GIF from giphy.com ends up with: media.giphy.com,
// media0–4.giphy.com or i.giphy.com, the asset under /media/ or a bare
// .gif/.webp. Such a link is a long opaque hash, so the composer and the
// message list draw it as a "GIF" badge instead. Header-only so the composer
// can share it without linking this TU into every widget test.
inline bool isGiphyMediaUrl(const QString &url) {
    const QUrl    u(url);
    const QString host = u.host().toLower();
    if (host != QLatin1String("giphy.com") && !host.endsWith(QLatin1String(".giphy.com")))
        return false;
    const QString path = u.path();
    return path.startsWith(QLatin1String("/media/")) ||
           path.endsWith(QLatin1String(".gif"), Qt::CaseInsensitive) ||
           path.endsWith(QLatin1String(".webp"), Qt::CaseInsensitive);
}

// True when a link's label says nothing the URL doesn't: empty, the URL itself
// (with or without its scheme), or Slack's truncated rendering of it.
bool isUrlLabel(const QString &label, const QString &url);

// True when `label` reads as a truncated rendering of `url`: it contains an
// ellipsis and its fragments appear, in order, in the scheme-less URL.
bool isShortenedUrlLabel(const QString &label, const QString &url);

// Display label rebuilt from the full URL: scheme stripped, tail elided with
// '…' past maxChars.
QString expandedLabel(const QString &url, int maxChars);

// Plain text of `t` with every shortened link label replaced by that link's
// full URL — for clipboard/export paths.
QString plainTextWithFullUrls(const TextWithEntities &t);

} // namespace LinkLabels
