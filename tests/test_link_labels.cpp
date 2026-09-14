// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 MSGA contributors. See LICENSE for details.
#include "text/link_labels.h"
#include <catch2/catch_test_macros.hpp>

static const QString kLongUrl =
    "https://akitravel.citycity.se/flights/rebook/%7B%22pnr%22%3A%22YU4SS7%22%7D";

TEST_CASE("shortened label is detected", "[link_labels]") {
    CHECK(
        LinkLabels::isShortenedUrlLabel(
            QString::fromUtf8("akitravel.citycity.se/flights/…/…"), kLongUrl
        )
    );
    CHECK(
        LinkLabels::isShortenedUrlLabel(
            QString::fromUtf8("akitravel.citycity.se/flights/reb…"), kLongUrl
        )
    );
    // ASCII "..." variant.
    CHECK(LinkLabels::isShortenedUrlLabel("akitravel.citycity.se/flights/...", kLongUrl));
}

TEST_CASE("real text labels are not detected", "[link_labels]") {
    CHECK_FALSE(LinkLabels::isShortenedUrlLabel("see this", kLongUrl));
    // Ellipsis, but not derived from this URL.
    CHECK_FALSE(LinkLabels::isShortenedUrlLabel(QString::fromUtf8("read more…"), kLongUrl));
    // Full label without ellipsis is not "shortened".
    CHECK_FALSE(LinkLabels::isShortenedUrlLabel("akitravel.citycity.se/flights", kLongUrl));
    CHECK_FALSE(LinkLabels::isShortenedUrlLabel(QString::fromUtf8("…"), QString()));
}

TEST_CASE("fragments must appear in order", "[link_labels]") {
    CHECK_FALSE(
        LinkLabels::isShortenedUrlLabel(
            QString::fromUtf8("rebook/…/akitravel.citycity.se"), kLongUrl
        )
    );
}

TEST_CASE("expandedLabel strips scheme and elides the tail", "[link_labels]") {
    CHECK(LinkLabels::expandedLabel("https://example.com/a", 100) == "example.com/a");
    const QString label = LinkLabels::expandedLabel(kLongUrl, 30);
    CHECK(label.size() == 30);
    CHECK(label.startsWith("akitravel.citycity.se/"));
    CHECK(label.endsWith(QChar(0x2026)));
}

TEST_CASE("plainTextWithFullUrls substitutes shortened spans only", "[link_labels]") {
    const QString    shortLabel = QString::fromUtf8("akitravel.citycity.se/flights/…/…");
    TextWithEntities t;
    t.text     = "check " + shortLabel + " and see this";
    t.entities = {
        {EntityType::Link, 6, (int)shortLabel.size(), kLongUrl},
        {EntityType::Link, 6 + (int)shortLabel.size() + 5, 8, "https://other.example/x"},
    };
    CHECK(LinkLabels::plainTextWithFullUrls(t) == "check " + kLongUrl + " and see this");
}

TEST_CASE("plainTextWithFullUrls is a no-op without shortened links", "[link_labels]") {
    TextWithEntities t;
    t.text     = "just words";
    t.entities = {{EntityType::Bold, 0, 4, {}}};
    CHECK(LinkLabels::plainTextWithFullUrls(t) == "just words");
}

// ── GIPHY media links ─────────────────────────────────────────────────────────

TEST_CASE("GIPHY media urls are detected across its hosts", "[link_labels][gif]") {
    CHECK(LinkLabels::isGiphyMediaUrl("https://media.giphy.com/media/abc123/giphy.gif"));
    CHECK(LinkLabels::isGiphyMediaUrl("https://media0.giphy.com/media/v1.Y2lk/200w.gif"));
    CHECK(LinkLabels::isGiphyMediaUrl("https://media4.giphy.com/media/abc/giphy-downsized.gif"));
    CHECK(LinkLabels::isGiphyMediaUrl("https://i.giphy.com/abc123.gif"));
    CHECK(LinkLabels::isGiphyMediaUrl("https://i.giphy.com/media/abc/giphy.webp"));
    // The site itself, or an unrelated host that merely mentions giphy.
    CHECK_FALSE(LinkLabels::isGiphyMediaUrl("https://giphy.com/gifs/cat-abc123"));
    CHECK_FALSE(LinkLabels::isGiphyMediaUrl("https://giphy.com/"));
    CHECK_FALSE(LinkLabels::isGiphyMediaUrl("https://notgiphy.com/media/abc/giphy.gif"));
    CHECK_FALSE(LinkLabels::isGiphyMediaUrl("https://example.com/media/giphy.com/x.gif"));
    CHECK_FALSE(LinkLabels::isGiphyMediaUrl("not a url"));
}

TEST_CASE("a label that only restates the url carries no title", "[link_labels][gif]") {
    const QString url = "https://media.giphy.com/media/abc123/giphy.gif";
    CHECK(LinkLabels::isUrlLabel("", url));
    CHECK(LinkLabels::isUrlLabel(url, url));
    CHECK(LinkLabels::isUrlLabel("media.giphy.com/media/abc123/giphy.gif", url));
    CHECK(LinkLabels::isUrlLabel(QString::fromUtf8("media.giphy.com/media/…/…"), url));
    CHECK_FALSE(LinkLabels::isUrlLabel("Dancing cat", url));
}
