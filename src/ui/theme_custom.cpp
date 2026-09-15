// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "theme_custom.h"
#include "theme.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QStringList>

#include <algorithm>
#include <array>
#include <cmath>

namespace Th {

namespace {

// "#RRGGBB" / "RRGGBB" / "#RGB" / "RGB", any case; invalid otherwise.
QColor parseHex(QString token) {
    token = token.trimmed();
    if (token.startsWith(QLatin1Char('#')))
        token.remove(0, 1);
    if (token.size() != 6 && token.size() != 3)
        return {};
    for (const QChar ch : token)
        if (!ch.isLetterOrNumber() || (ch.isLetter() && ch.toLower() > QLatin1Char('f')))
            return {};
    const QColor c(QLatin1Char('#') + token);
    return c.isValid() ? c : QColor();
}

QString hex(const QColor &c) {
    return c.name(QColor::HexRgb).toUpper();
}

// One `ia_theme` slot: `{"hex":"#…","palette":"name"}`, or leniently a bare
// string holding either. The hex wins when it is valid; a known palette name
// resolves against our swatches; anything else falls back to `fallback`.
CustomTheme::Slot parseSlot(const QJsonValue &v, const CustomTheme::Slot &fallback) {
    QString hexText, palette;
    if (v.isObject()) {
        const QJsonObject o = v.toObject();
        hexText             = o.value(QLatin1String("hex")).toString();
        palette             = o.value(QLatin1String("palette")).toString();
    } else if (v.isString()) {
        const QString s = v.toString();
        if (parseHex(s).isValid())
            hexText = s;
        else
            palette = s;
    }
    if (const QColor c = parseHex(hexText); c.isValid())
        return {c, swatchNameFor(c)};
    if (const Swatch *sw = swatchByName(palette))
        return {sw->color, sw->name};
    return fallback;
}

QJsonObject slotJson(const CustomTheme::Slot &s) {
    QJsonObject o;
    o.insert(QLatin1String("hex"), hex(s.color));
    if (!s.palette.isEmpty())
        o.insert(QLatin1String("palette"), s.palette);
    return o;
}

std::optional<CustomTheme> parseJsonTheme(const QString &text) {
    QJsonParseError     err{};
    const QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject())
        return std::nullopt;
    const QJsonObject o = doc.object();

    static const std::array<const char *, 4> kSlots = {
        "primary", "highlight1", "highlight2", "important"
    };
    const bool anySlot = std::any_of(kSlots.begin(), kSlots.end(), [&o](const char *k) {
        return o.contains(QLatin1String(k));
    });
    if (!anySlot)
        return std::nullopt; // some other JSON

    const CustomTheme def = defaultCustomTheme();
    CustomTheme       t;
    t.primary    = parseSlot(o.value(QLatin1String("primary")), def.primary);
    t.highlight1 = parseSlot(o.value(QLatin1String("highlight1")), def.highlight1);
    t.highlight2 = parseSlot(o.value(QLatin1String("highlight2")), def.highlight2);
    t.important  = parseSlot(o.value(QLatin1String("important")), def.important);
    t.brightness = std::clamp(
        o.value(QLatin1String("brightness")).toInt(CustomTheme::kBrightnessNeutral),
        CustomTheme::kBrightnessMin,
        CustomTheme::kBrightnessMax
    );
    t.sidebarInverted = o.value(QLatin1String("sidebarInverted")).toBool(true);
    t.gradient        = o.value(QLatin1String("gradient")).toBool(true);

    const QJsonObject pins = o.value(QLatin1String("pins")).toObject();
    t.pins.itemHover       = parseHex(pins.value(QLatin1String("itemHover")).toString());
    t.pins.itemSelText     = parseHex(pins.value(QLatin1String("itemSelText")).toString());
    t.pins.itemText        = parseHex(pins.value(QLatin1String("itemText")).toString());
    t.pins.titleBarBg      = parseHex(pins.value(QLatin1String("titleBarBg")).toString());
    t.pins.titleBarText    = parseHex(pins.value(QLatin1String("titleBarText")).toString());
    return t;
}

} // namespace

QString serializeCustomTheme(const CustomTheme &t) {
    QJsonObject o;
    o.insert(QLatin1String("primary"), slotJson(t.primary));
    o.insert(QLatin1String("highlight1"), slotJson(t.highlight1));
    o.insert(QLatin1String("highlight2"), slotJson(t.highlight2));
    o.insert(QLatin1String("important"), slotJson(t.important));
    o.insert(QLatin1String("brightness"), t.brightness);
    o.insert(QLatin1String("sidebarInverted"), t.sidebarInverted);
    o.insert(QLatin1String("useCustomHex"), true);
    o.insert(QLatin1String("gradient"), t.gradient);

    QJsonObject pins;
    const auto  pin = [&pins](const char *key, const QColor &c) {
        if (c.isValid())
            pins.insert(QLatin1String(key), hex(c));
    };
    pin("itemHover", t.pins.itemHover);
    pin("itemSelText", t.pins.itemSelText);
    pin("itemText", t.pins.itemText);
    pin("titleBarBg", t.pins.titleBarBg);
    pin("titleBarText", t.pins.titleBarText);
    if (!pins.isEmpty())
        o.insert(QLatin1String("pins"), pins);
    return QString::fromUtf8(QJsonDocument(o).toJson(QJsonDocument::Compact));
}

std::optional<CustomTheme> parseLegacyTheme(const QString &text) {
    static const QRegularExpression kSep(QStringLiteral("[,\\s]+"));
    const QStringList               tokens = text.trimmed().split(kSep, Qt::SkipEmptyParts);
    if (tokens.size() != 8 && tokens.size() != 10)
        return std::nullopt;
    std::vector<QColor> colors;
    for (const QString &tok : tokens) {
        const QColor c = parseHex(tok);
        if (!c.isValid())
            return std::nullopt;
        colors.push_back(c);
    }
    // column_bg, menu_bg, active_item, active_item_text, hover_item, text_color,
    // active_presence, badge[, top_nav_bg, top_nav_text]
    const auto  slot = [](const QColor &c) { return CustomTheme::Slot{c, swatchNameFor(c)}; };
    CustomTheme t;
    t.primary          = slot(colors[0]);
    t.highlight1       = slot(colors[2]);
    t.pins.itemSelText = colors[3];
    t.pins.itemHover   = colors[4];
    t.pins.itemText    = colors[5];
    t.highlight2       = slot(colors[6]);
    t.important        = slot(colors[7]);
    if (colors.size() == 10) {
        t.pins.titleBarBg   = colors[8];
        t.pins.titleBarText = colors[9];
    }
    return t;
}

std::optional<CustomTheme> parseCustomTheme(const QString &text) {
    const QString trimmed = text.trimmed();
    if (trimmed.isEmpty())
        return std::nullopt;
    if (trimmed.startsWith(QLatin1Char('{')))
        return parseJsonTheme(trimmed);
    return parseLegacyTheme(trimmed);
}

QString legacyShareString(const CustomTheme &, const Theme &b) {
    // Slot order per the legacy format; the derived ones read off the built
    // theme so the copy describes exactly what is on screen.
    const std::array<QColor, 10> order = {
        b.nav.bg,                  // column_bg
        b.nav.itemHover,           // menu_bg
        b.nav.itemSelected,        // active_item
        b.nav.itemSelectedText,    // active_item_text
        b.nav.itemHover,           // hover_item
        b.nav.itemText,            // text_color
        b.presence.online,         // active_presence
        b.badge.mention,           // badge
        b.titleBar.bg,             // top_nav_bg
        b.titleBar.controlDefault, // top_nav_text
    };
    QStringList out;
    for (const QColor &c : order)
        out << hex(c);
    return out.join(QLatin1Char(','));
}

double contrastRatio(const QColor &a, const QColor &b) {
    const auto lum = [](const QColor &c) {
        const auto lin = [](double v) {
            return v <= 0.03928 ? v / 12.92 : std::pow((v + 0.055) / 1.055, 2.4);
        };
        return 0.2126 * lin(c.redF()) + 0.7152 * lin(c.greenF()) + 0.0722 * lin(c.blueF());
    };
    const double la = lum(a), lb = lum(b);
    return (std::max(la, lb) + 0.05) / (std::min(la, lb) + 0.05);
}

} // namespace Th
