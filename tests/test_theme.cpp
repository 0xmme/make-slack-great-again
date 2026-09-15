// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include "ui/file_dialog_utils.h"
#include "ui/theme.h"
#include "ui/theme_manager.h"

#include <QApplication>
#include <QFileDialog>
#include <QGuiApplication>
#include <QLabel>
#include <QSettings>
#include <QSignalSpy>
#include <QTemporaryDir>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    app.setApplicationName("msga-test-theme");
    app.setOrganizationName("msga-test");
    // ThemeManager persists via QSettings("msga", "msga") — redirect user-scope
    // storage so tests never touch the real config.
    static QTemporaryDir settingsDir;
    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, settingsDir.path());
    // The ctest entry test_theme_migration runs this binary with a pre-mode
    // config (a single "appearance/theme" key) so the ThemeManager constructor's
    // one-time migration can be exercised; it runs once per process.
    const QByteArray seed = qgetenv("MSGA_TEST_SEED_THEME");
    if (!seed.isEmpty())
        QSettings("msga", "msga").setValue("appearance/theme", QString::fromUtf8(seed));
    return Catch::Session().run(argc, argv);
}

TEST_CASE("theme registry", "[theme]") {
    const auto &themes = Th::availableThemes();
    REQUIRE(themes.size() >= 2);
    CHECK(themes[0].id == "purple");   // default first
    CHECK(themes[1].id == "charcoal"); // second slot in the picker

    const auto *purple   = Th::themeById("purple");
    const auto *charcoal = Th::themeById("charcoal");
    const auto *blue     = Th::themeById("blue");
    REQUIRE(purple != nullptr);
    REQUIRE(charcoal != nullptr);
    REQUIRE(blue != nullptr);
    CHECK(purple == &Th::defaultTheme());

    CHECK(Th::themeById("does-not-exist") == nullptr);
}

TEST_CASE("light themes retint chrome only; content surfaces are shared", "[theme]") {
    const auto &purple = *Th::themeById("purple");

    for (const auto &info : Th::availableThemes()) {
        if (info.id == QLatin1String("purple") || info.id == QLatin1String("charcoal"))
            continue; // charcoal is the dark theme — it retints content by design
        INFO("theme: " << info.id.toStdString());
        const auto &t = *info.theme;

        // Chrome differs…
        CHECK(t.nav.bg != purple.nav.bg);
        CHECK(t.accent.def != purple.accent.def);
        CHECK(t.titleBar.bg != purple.titleBar.bg);
        CHECK(t.icon.accent == t.accent.def);
        CHECK(t.titleBar.bg == t.nav.bg);

        // …content-side tokens must stay identical (copy-and-patch guarantee).
        CHECK(t.text.primary == purple.text.primary);
        CHECK(t.surface.content == purple.surface.content);
        CHECK(t.message.codeBlockBg == purple.message.codeBlockBg);
        CHECK(t.badge.mention == purple.badge.mention);
        CHECK(t.fonts.base == purple.fonts.base);
    }
}

TEST_CASE("charcoal is a coherent dark theme", "[theme]") {
    const auto &t = *Th::themeById("charcoal");

    // Dark surfaces, light text — and enough spread between them to read.
    CHECK(t.surface.content.lightnessF() < 0.2);
    CHECK(t.surface.raised.lightnessF() < 0.25);
    CHECK(t.surface.sunken.lightnessF() < t.surface.content.lightnessF());
    CHECK(t.text.primary.lightnessF() > 0.75);
    CHECK(t.text.secondary.lightnessF() > 0.5);
    CHECK(t.text.primary.lightnessF() - t.surface.content.lightnessF() > 0.5);

    // Alpha overlays must LIGHTEN on dark surfaces, not darken.
    CHECK(t.message.hover.lightnessF() > 0.9);
    CHECK(t.surface.highlight.lightnessF() > t.surface.content.lightnessF());

    // Sidebar depth: chats list darker than the content area, rail darkest —
    // the light themes' white-plate derivation must not flip this on dark.
    CHECK(t.nav.primary.lightnessF() < t.surface.content.lightnessF());
    CHECK(t.nav.bg.lightnessF() < t.nav.primary.lightnessF());

    // Filled controls stay visible: accent face vs the surfaces it sits on,
    // and its label vs the face.
    CHECK(t.accent.def.lightnessF() - t.surface.raised.lightnessF() > 0.1);
    CHECK(t.accent.text.lightnessF() - t.accent.def.lightnessF() > 0.4);

    // Content chrome that borders text follows the dark surfaces.
    CHECK(t.composer.bg.lightnessF() < 0.25);
    CHECK(t.message.codeBlockBg.lightnessF() < 0.25);
    CHECK(t.contextMenu.bg.lightnessF() < 0.25);
    CHECK(t.divider.def.lightnessF() < 0.4);

    // Structure/type scales stay shared with the base theme.
    const auto &purple = *Th::themeById("purple");
    CHECK(t.fonts.base == purple.fonts.base);
    CHECK(t.spacing.md == purple.spacing.md);
    CHECK(t.badge.mention == purple.badge.mention);
}

TEST_CASE("ThemeManager switches, persists and ignores unknown ids", "[theme]") {
    auto &mgr = ThemeManager::instance();
    CHECK(mgr.themeId() == "purple"); // fresh settings → default

    QSignalSpy spy(&mgr, &ThemeManager::themeChanged);

    mgr.setThemeById("blue");
    CHECK(mgr.themeId() == "blue");
    CHECK(mgr.theme().nav.bg == Th::themeById("blue")->nav.bg);
    CHECK(spy.count() == 1);
    CHECK(QSettings("msga", "msga").value("appearance/theme").toString() == QStringLiteral("blue"));

    mgr.setThemeById("blue"); // no-op: already active
    CHECK(spy.count() == 1);

    mgr.setThemeById("does-not-exist"); // ignored
    CHECK(mgr.themeId() == "blue");
    CHECK(spy.count() == 1);

    mgr.setThemeById("purple");
    CHECK(mgr.themeId() == "purple");
    CHECK(spy.count() == 2);
    CHECK(
        QSettings("msga", "msga").value("appearance/theme").toString() == QStringLiteral("purple")
    );
}

TEST_CASE("registry classifies content darkness", "[theme]") {
    CHECK_FALSE(Th::isDarkTheme(*Th::themeById("purple")));
    CHECK_FALSE(Th::isDarkTheme(*Th::themeById("blue")));
    CHECK_FALSE(Th::isDarkTheme(*Th::themeById("green")));
    CHECK(Th::isDarkTheme(*Th::themeById("charcoal")));
    CHECK(Th::isDarkTheme(Th::defaultDarkTheme()));
    CHECK_FALSE(Th::isDarkTheme(Th::defaultTheme()));
}

TEST_CASE("colour mode: default is System, slots are per mode, persisted", "[theme][mode]") {
    auto &mgr = ThemeManager::instance();
    // Reset to a known state (earlier cases may have moved the light slot).
    mgr.setMode(ThemeManager::ColorMode::System);
    mgr.setThemeIdFor(false, "purple");
    mgr.setThemeIdFor(true, "charcoal");

    // Default mode is System — the same as the official Slack desktop app.
    CHECK(ThemeManager::modeFromId("") == ThemeManager::ColorMode::System);
    CHECK(ThemeManager::modeFromId("bogus") == ThemeManager::ColorMode::System);
    CHECK(ThemeManager::modeId(ThemeManager::ColorMode::System) == "system");
    CHECK(ThemeManager::modeFromId("light") == ThemeManager::ColorMode::Light);
    CHECK(ThemeManager::modeFromId("dark") == ThemeManager::ColorMode::Dark);

    // The offscreen platform reports no scheme → System resolves to light.
    CHECK(mgr.mode() == ThemeManager::ColorMode::System);
    CHECK_FALSE(mgr.effectiveDark());
    CHECK(mgr.themeId() == "purple");

    QSignalSpy themeSpy(&mgr, &ThemeManager::themeChanged);
    QSignalSpy modeSpy(&mgr, &ThemeManager::modeChanged);

    // Fixed dark: renders the dark slot.
    mgr.setMode(ThemeManager::ColorMode::Dark);
    CHECK(mgr.effectiveDark());
    CHECK(mgr.themeId() == "charcoal");
    CHECK(Th::isDarkTheme(mgr.theme()));
    CHECK(themeSpy.count() == 1);
    CHECK(modeSpy.count() == 1);
    CHECK(QSettings("msga", "msga").value("appearance/mode").toString() == "dark");

    // Editing the light slot while dark is shown changes nothing on screen…
    mgr.setThemeIdFor(false, "blue");
    CHECK(mgr.themeId() == "charcoal");
    CHECK(themeSpy.count() == 1);
    CHECK(mgr.themeIdFor(false) == "blue");
    CHECK(QSettings("msga", "msga").value("appearance/theme").toString() == "blue");
    CHECK(mgr.themeIdFor(true) == "charcoal"); // untouched default: not written until changed

    // …until the mode flips to it.
    mgr.setMode(ThemeManager::ColorMode::Light);
    CHECK(mgr.themeId() == "blue");
    CHECK(themeSpy.count() == 2);

    // A theme may only fill the slot of its own darkness.
    mgr.setThemeIdFor(true, "blue"); // light theme into the dark slot → ignored
    CHECK(mgr.themeIdFor(true) == "charcoal");
    mgr.setThemeIdFor(false, "charcoal"); // dark theme into the light slot → ignored
    CHECK(mgr.themeIdFor(false) == "blue");
    mgr.setThemeIdFor(true, "nope");
    CHECK(mgr.themeIdFor(true) == "charcoal");

    // setThemeById routes by the theme's darkness — the old single-slot API
    // keeps working for callers that don't know about modes.
    mgr.setThemeById("charcoal"); // dark slot (already charcoal → no-op)
    CHECK(themeSpy.count() == 2);
    mgr.setThemeById("green"); // light slot, which is on screen
    CHECK(mgr.themeId() == "green");
    CHECK(themeSpy.count() == 3);

    // Same mode again is a no-op.
    mgr.setMode(ThemeManager::ColorMode::Light);
    CHECK(themeSpy.count() == 3);

    // Back to System (→ light here): nothing new on screen, but the mode
    // observers still hear about it.
    const int modeBefore = modeSpy.count();
    mgr.setMode(ThemeManager::ColorMode::System);
    CHECK(mgr.themeId() == "green");
    CHECK(themeSpy.count() == 3);
    CHECK(modeSpy.count() == modeBefore + 1);

    mgr.setThemeIdFor(false, "purple");
}

TEST_CASE("colour mode: System follows the OS scheme live", "[theme][mode]") {
    auto &mgr = ThemeManager::instance();
    mgr.setMode(ThemeManager::ColorMode::System);
    mgr.setThemeIdFor(false, "purple");
    mgr.setThemeIdFor(true, "charcoal");
    REQUIRE(mgr.themeId() == "purple");

    QSignalSpy themeSpy(&mgr, &ThemeManager::themeChanged);

    // The offscreen platform theme reports no scheme (and ignores
    // QStyleHints::setColorScheme), so drive the resolver through the override
    // the way a portal-less desktop would; refreshSystemScheme() is what the
    // colorSchemeChanged signal is wired to.
    qputenv("MSGA_SYSTEM_COLOR_SCHEME", "dark");
    mgr.refreshSystemScheme();
    CHECK(mgr.effectiveDark());
    CHECK(mgr.themeId() == "charcoal");
    CHECK(themeSpy.count() == 1);

    // A fixed mode ignores the OS…
    mgr.setMode(ThemeManager::ColorMode::Light);
    CHECK(mgr.themeId() == "purple");
    qputenv("MSGA_SYSTEM_COLOR_SCHEME", "light");
    mgr.refreshSystemScheme();
    qputenv("MSGA_SYSTEM_COLOR_SCHEME", "dark");
    mgr.refreshSystemScheme();
    CHECK(mgr.themeId() == "purple");

    // …and System picks it back up on re-entry.
    mgr.setMode(ThemeManager::ColorMode::System);
    CHECK(mgr.themeId() == "charcoal");

    qunsetenv("MSGA_SYSTEM_COLOR_SCHEME");
    mgr.refreshSystemScheme();
    CHECK(mgr.themeId() == "purple");
}

TEST_CASE("legacy charcoal pick migrates to a fixed dark mode", "[theme][migration]") {
    // Only meaningful when main() seeded the pre-mode config (see there).
    if (qgetenv("MSGA_TEST_SEED_THEME") != "charcoal")
        SKIP("run via test_theme_migration");
    auto &mgr = ThemeManager::instance();
    // Charcoal was the only dark-content theme, so the pick meant "dark mode":
    // keep it dark rather than flipping the user to System on upgrade.
    CHECK(mgr.mode() == ThemeManager::ColorMode::Dark);
    CHECK(mgr.themeId() == "charcoal");
    CHECK(mgr.themeIdFor(true) == "charcoal");
    CHECK(mgr.themeIdFor(false) == "purple");
    QSettings s("msga", "msga");
    CHECK(s.value("appearance/mode").toString() == "dark");
    CHECK(s.value("appearance/theme").toString() == "purple");
    CHECK(s.value("appearance/themeDark").toString() == "charcoal");
}

TEST_CASE("stock file dialog readable whatever the OS palette", "[theme]") {
    // Issue #18: with no native dialog helper Qt shows its widget-based
    // QFileDialog, which inherits an ancestor `QWidget { background: … }`
    // stylesheet (theme surface) while QStyleSheetStyle rebuilds each child's
    // text colors from the OS palette — white-on-white when the OS theme is
    // dark and the app theme is light (and inverted for charcoal). The dialog
    // must pin its text to the same theme its backgrounds come from.
    const QPalette appPalette = qApp->palette();
    QPalette       osDark     = appPalette;
    for (auto role : {QPalette::WindowText, QPalette::Text, QPalette::ButtonText})
        osDark.setColor(role, QColor("#FCFCFC"));
    qApp->setPalette(osDark);

    for (const auto &info : Th::availableThemes()) {
        INFO("theme: " << info.id.toStdString());
        ThemeManager::instance().setTheme(*info.theme);

        // Stand-in for MainWindow's right panel, whose stylesheet cascades
        // into every parented dialog.
        QWidget panel;
        panel.setStyleSheet(
            QString("QWidget { background: %1; }").arg(Th::qss(Th::c().surface.content))
        );

        QFileDialog dlg(&panel);
        dlg.setOption(QFileDialog::DontUseNativeDialog);
        Ui::applyFileDialogTheme(&dlg);
        dlg.show();

        auto *label = dlg.findChild<QLabel *>("fileNameLabel");
        REQUIRE(label != nullptr);
        CHECK(label->palette().color(QPalette::WindowText) == Th::c().text.primary);
    }

    qApp->setPalette(appPalette);
    ThemeManager::instance().setTheme(Th::defaultTheme());
}
