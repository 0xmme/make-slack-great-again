// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include "theme.h"
#include <QFont>
#include <QObject>

namespace Th {
const Theme &defaultTheme();     // light-mode default (purple)
const Theme &defaultDarkTheme(); // dark-mode default (charcoal)
} // namespace Th

class ThemeManager : public QObject {
    Q_OBJECT
public:
    // Which content mode the app renders in. `System` follows the OS colour
    // scheme (QStyleHints::colorScheme; an Unknown answer — e.g. a bare Linux
    // WM without the settings portal — counts as light). Persisted as
    // QSettings "appearance/mode"; the default is System, like the official
    // Slack desktop app.
    enum class ColorMode { Light, Dark, System };

    static ThemeManager &instance();

    const Th::Theme &theme() const { return _theme; }
    // Id of the theme currently on screen (the active mode's slot).
    const QString   &themeId() const { return _themeId; }

    // Replace the active theme and notify all subscribers.
    void setTheme(const Th::Theme &theme);

    // Assign a preset to the slot currently on screen (the effective mode's),
    // persist and re-resolve. Unknown ids are ignored.
    void setThemeById(const QString &id);

    // ── Colour mode + per-mode theme slots ────────────────────────────────
    ColorMode      mode() const { return _mode; }
    void           setMode(ColorMode mode);
    // The mode actually rendered: System resolved against the OS scheme.
    bool           effectiveDark() const;
    // Re-resolve System mode against the OS scheme. Wired internally to
    // QStyleHints::colorSchemeChanged; public so a change to the
    // MSGA_SYSTEM_COLOR_SCHEME override ("light" | "dark" — forces what System
    // resolves to; for headless verification and desktops without a settings
    // portal) can be picked up without a restart.
    void           refreshSystemScheme();
    // The preset id each mode renders with (QSettings "appearance/theme" for
    // light — the pre-mode key, so old installs keep their pick — and
    // "appearance/themeDark" for dark). Every preset renders over both modes;
    // the slot picks the chrome, the mode picks the content.
    const QString &themeIdFor(bool dark) const { return dark ? _darkId : _lightId; }
    // Set one slot explicitly. Ignored when `id` is neither a registry preset
    // nor kCustomId.
    void           setThemeIdFor(bool dark, const QString &id);

    // ── Custom theme ──────────────────────────────────────────────────────
    // The slot value for the user-defined chrome (Th::CustomTheme); one custom
    // theme, rendered over both content modes like a preset. Persisted as JSON
    // under QSettings "appearance/customTheme".
    static constexpr auto  kCustomId = "custom";
    const Th::CustomTheme &customTheme() const { return _custom; }
    // Replace the custom theme: persists, rebuilds both variants, emits
    // customThemeChanged, and re-renders when the slot on screen is custom.
    void                   setCustomTheme(const Th::CustomTheme &t);
    // The built custom theme for one content mode (stable address: preview
    // cards keep a reference and repaint on customThemeChanged).
    const Th::Theme &customVariant(bool dark) const { return dark ? _customDark : _customLight; }
    // Preset or custom: what a slot id renders as for one mode; nullptr for
    // an unknown id.
    const Th::Theme *themeFor(const QString &id, bool dark) const;

    static QString   modeId(ColorMode mode);        // "light" | "dark" | "system"
    static ColorMode modeFromId(const QString &id); // unknown → System

    // UI font size variant ("small" | "medium" | "large"): a multiplier applied
    // over the active theme's px font scale, so every widget that sizes text
    // from Th::c().fonts follows. Persisted (QSettings "appearance/fontSize");
    // setting it re-derives the theme from its pristine registry entry (the
    // scale never compounds) and notifies via themeChanged.
    const QString &fontSizeId() const { return _fontSizeId; }
    void           setFontSizeId(const QString &id);
    // The active multiplier (0.9 / 1.0 / 1.15) for text-driven GEOMETRY that
    // isn't sized from a font (fixed row heights, etc.). Text itself should
    // derive from Th::c().fonts or QApplication::font(), not from this.
    double         fontFactor() const;

signals:
    void themeChanged();
    // The colour mode setting or the OS scheme it follows changed. Always
    // accompanied by themeChanged when the rendered theme differs; emitted on
    // its own when it doesn't (so mode-aware UI, like the "currently dark"
    // hint, still refreshes).
    void modeChanged();
    // The custom theme's definition changed (always after both variants were
    // rebuilt; themeChanged follows only when it is on screen).
    void customThemeChanged();

private:
    explicit ThemeManager(QObject *parent = nullptr);

    // Scale the APPLICATION font from _baseAppFont by the active factor. The
    // message renderer (and every default-font widget) derives its text size
    // from QApplication::font(), not from Th::c().fonts — without this, the
    // font-size setting would only reach px-token'd chrome labels.
    void applyAppFontScale();

    // The registry theme the effective mode's slot names (falling back to that
    // mode's default when the slot holds a stale id).
    const Th::Theme &resolvedTheme() const;
    // Re-apply the slot the effective mode selects; notifies when it changed.
    void             reapply();

    Th::Theme _theme;
    QString   _themeId;
    bool      _themeDark = false; // content mode of the theme on screen
    ColorMode _mode      = ColorMode::System;
    QString   _lightId;
    QString   _darkId;
    QString   _fontSizeId;
    QFont     _baseAppFont; // app font as set by main() — scaling never compounds

    Th::CustomTheme _custom;
    Th::Theme       _customLight;
    Th::Theme       _customDark;
    void            rebuildCustom();
};
