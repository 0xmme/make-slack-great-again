// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
// A user-defined chrome palette in Slack's shape: four colour slots plus the
// brightness / darker-sidebar / gradient switches, so a theme copied out of
// msga is what Slack stores (`ia_theme`) and a theme pasted from Slack or any
// theme site (the legacy 8/10-hex string) imports. Parsing, serialising and
// the contrast check live here; the slot → token derivation and the swatch
// table live in theme.cpp (colour literals stay in theme code).
#pragma once

#include <QColor>
#include <QString>

#include <optional>

namespace Th {

struct CustomTheme {
    // One Slack slot: the resolved colour, and the swatch name it was picked
    // from when it was (empty for a hex pick / an unknown Slack palette).
    struct Slot {
        QColor  color;
        QString palette;

        bool operator==(const Slot &) const = default;
    };

    Slot primary;    // rail; list surface, hover, gradients, title bar derive from it
    Slot highlight1; // selection pill, accent set, icon accent
    Slot highlight2; // presence dot
    Slot important;  // mention badge

    int  brightness      = kBrightnessNeutral; // 0–10; shifts the rail's lightness
    bool sidebarInverted = true;               // dark rail over light content ("Darker sidebar")
    bool gradient        = true;               // vertical sidebar gradient on/off

    // Optional pins a legacy string names outright; derivation never overwrites
    // a valid one. Invalid (default) = derive.
    struct Pins {
        QColor itemHover;    // menu_bg / hover_item
        QColor itemSelText;  // active_item_text
        QColor itemText;     // text_color
        QColor titleBarBg;   // top_nav_bg
        QColor titleBarText; // top_nav_text

        bool operator==(const Pins &) const = default;
    } pins;

    static constexpr int kBrightnessMin     = 0;
    static constexpr int kBrightnessMax     = 10;
    static constexpr int kBrightnessNeutral = 6; // Slack's stored default; the rail as designed

    bool operator==(const CustomTheme &) const = default;
};

// ── Serialisation ────────────────────────────────────────────────────────────

// Compact JSON in the `ia_theme` shape (`{"primary":{"hex":"#3F0E40","palette":
// "aubergine"},…,"brightness":6,"sidebarInverted":true,"useCustomHex":true}`)
// plus our `gradient` and `pins` keys, which Slack ignores. What is persisted
// under QSettings "appearance/customTheme" and what "Copy theme" offers.
QString serializeCustomTheme(const CustomTheme &t);

// Accepts any of: our JSON above, Slack's `ia_theme` JSON (palette names
// resolve against Th::swatches(); an unknown name uses the slot's `hex` when
// present, else aubergine), or a legacy share string — 8 or 10 comma- or
// whitespace-separated hex colours (with or without `#`, 3 or 6 digits, any
// case) in Slack's slot order: column_bg, menu_bg, active_item,
// active_item_text, hover_item, text_color, active_presence, badge[,
// top_nav_bg, top_nav_text]. Anything else → nullopt.
std::optional<CustomTheme> parseCustomTheme(const QString &text);

// The legacy variant only (see parseCustomTheme for the format).
std::optional<CustomTheme> parseLegacyTheme(const QString &text);

// The 10-value legacy share string for `t`, in Slack's slot order — what
// Slack's "Import theme" field and every theme site accept. The derived slots
// (menu_bg/hover_item, active_item_text, text_color, top_nav_*) come from the
// built theme; pass the variant that is on screen so the copy matches it.
struct Theme;
QString legacyShareString(const CustomTheme &t, const Theme &built);

// WCAG 2 contrast ratio between two opaque colours (1 … 21).
double contrastRatio(const QColor &a, const QColor &b);

} // namespace Th
