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

namespace {

// Tokens the chrome step writes; every one must come out a real colour for
// every preset × mode (an unset ChromeSpec field would leave one invalid).
void checkChromeTokensValid(const Th::Theme &t) {
    for (const QColor *c :
         {&t.nav.bg,
          &t.nav.primary,
          &t.nav.workspaceBubble,
          &t.nav.itemSelected,
          &t.nav.itemSelectedText,
          &t.nav.itemHover,
          &t.nav.itemText,
          &t.nav.itemTextDim,
          &t.nav.scrollThumb,
          &t.nav.scrollThumbHover,
          &t.nav.extBadgeBg,
          &t.nav.extBadgeText,
          &t.nav.bgGradTop,
          &t.nav.bgGradBottom,
          &t.nav.primaryGradTop,
          &t.nav.primaryGradBottom,
          &t.accent.def,
          &t.accent.hover,
          &t.accent.pressed,
          &t.accent.dark,
          &t.accent.subtleBg,
          &t.accent.text,
          &t.icon.accent,
          &t.titleBar.bg,
          &t.titleBar.controlDefault,
          &t.titleBar.controlHover,
          &t.presence.online,
          &t.badge.mention})
        CHECK(c->isValid());
}

} // namespace

TEST_CASE("theme registry", "[theme]") {
    const auto &themes = Th::availableThemes();
    REQUIRE(themes.size() >= 2);
    CHECK(themes[0].id == "purple");   // default first
    CHECK(themes[1].id == "charcoal"); // second slot in the picker

    // Every preset renders over both content modes.
    for (const auto &info : themes) {
        INFO("theme: " << info.id.toStdString());
        REQUIRE(info.light != nullptr);
        REQUIRE(info.dark != nullptr);
        CHECK(info.variant(false) == info.light);
        CHECK(info.variant(true) == info.dark);
        CHECK(Th::themeById(info.id, false) == info.light);
        CHECK(Th::themeById(info.id, true) == info.dark);
        CHECK_FALSE(Th::isDarkTheme(*info.light));
        CHECK(Th::isDarkTheme(*info.dark));
        checkChromeTokensValid(*info.light);
        checkChromeTokensValid(*info.dark);
    }

    CHECK(Th::themeById("purple", false) == &Th::defaultTheme());
    CHECK(Th::themeById("charcoal", true) == &Th::defaultDarkTheme());
    CHECK(Th::themeById("does-not-exist", false) == nullptr);
    CHECK(Th::themeById("does-not-exist", true) == nullptr);
}

TEST_CASE("presets retint chrome only; content surfaces are shared per mode", "[theme]") {
    for (const bool dark : {false, true}) {
        const auto &purple = *Th::themeById("purple", dark);
        for (const auto &info : Th::availableThemes()) {
            INFO("theme: " << info.id.toStdString() << (dark ? " dark" : " light"));
            const auto &t = *info.variant(dark);

            // Chrome is coherent…
            CHECK(t.titleBar.bg == t.nav.bg);
            CHECK(t.titleBar.controlDefault == t.nav.itemTextDim);
            CHECK(t.titleBar.controlHover == t.nav.itemText);
            if (!dark)
                CHECK(t.icon.accent == t.accent.def);
            if (info.id != QLatin1String("purple")) {
                CHECK(t.nav.bg != purple.nav.bg);
                CHECK(t.accent.def != purple.accent.def);
            }

            // …content-side tokens are identical across presets (copy-and-patch).
            CHECK(t.text.primary == purple.text.primary);
            CHECK(t.surface.content == purple.surface.content);
            CHECK(t.message.codeBlockBg == purple.message.codeBlockBg);
            CHECK(t.composer.bg == purple.composer.bg);
            CHECK(t.badge.mention == purple.badge.mention);
            CHECK(t.fonts.base == purple.fonts.base);
        }
    }
}

TEST_CASE("a preset's chrome is the same over both content modes", "[theme]") {
    for (const auto &info : Th::availableThemes()) {
        INFO("theme: " << info.id.toStdString());
        const auto &l = *info.light;
        const auto &d = *info.dark;
        CHECK(l.nav.bg == d.nav.bg);
        CHECK(l.nav.itemSelected == d.nav.itemSelected);
        CHECK(l.nav.itemSelectedText == d.nav.itemSelectedText);
        CHECK(l.nav.workspaceBubble == d.nav.workspaceBubble);
        CHECK(l.nav.itemText == d.nav.itemText);
        CHECK(l.nav.itemTextDim == d.nav.itemTextDim);
        CHECK(l.titleBar.bg == d.titleBar.bg);
        // The list plate is thinner over dark content, but always lightens the rail.
        CHECK(l.nav.primary.lightnessF() > l.nav.bg.lightnessF());
        CHECK(d.nav.primary.lightnessF() > d.nav.bg.lightnessF());
        CHECK(d.nav.primary.lightnessF() < l.nav.primary.lightnessF());
    }
}

TEST_CASE("every dark variant is a coherent dark theme", "[theme]") {
    for (const auto &info : Th::availableThemes()) {
        INFO("theme: " << info.id.toStdString());
        const auto &t = *info.dark;

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

        // Filled controls stay visible: accent face vs the surfaces it sits on,
        // and its label vs the face. Brand accents tuned for white content are
        // lifted for dark content.
        CHECK(t.accent.def.lightnessF() - t.surface.raised.lightnessF() > 0.1);
        CHECK(t.accent.hover.lightnessF() > t.accent.def.lightnessF());
        CHECK(t.accent.pressed.lightnessF() < t.accent.def.lightnessF());
        CHECK(t.accent.text.lightnessF() - t.accent.def.lightnessF() > 0.4);
        CHECK(t.icon.accent.lightnessF() > 0.5);

        // Content chrome that borders text follows the dark surfaces.
        CHECK(t.composer.bg.lightnessF() < 0.25);
        CHECK(t.message.codeBlockBg.lightnessF() < 0.25);
        CHECK(t.contextMenu.bg.lightnessF() < 0.25);
        CHECK(t.divider.def.lightnessF() < 0.4);

        // Structure/type scales stay shared with the base theme.
        const auto &purple = *Th::themeById("purple", false);
        CHECK(t.fonts.base == purple.fonts.base);
        CHECK(t.spacing.md == purple.spacing.md);
        CHECK(t.badge.mention == purple.badge.mention);
    }

    // Graphite over dark content is the full dark mode: chats list darker than
    // the content area, rail darkest — the light themes' white-plate derivation
    // must not flip this on dark.
    const auto &charcoal = *Th::themeById("charcoal", true);
    CHECK(charcoal.nav.primary.lightnessF() < charcoal.surface.content.lightnessF());
    CHECK(charcoal.nav.bg.lightnessF() < charcoal.nav.primary.lightnessF());
}

TEST_CASE("light charcoal is light content under graphite chrome", "[theme]") {
    const auto &t      = *Th::themeById("charcoal", false);
    const auto &purple = *Th::themeById("purple", false);
    CHECK_FALSE(Th::isDarkTheme(t));
    CHECK(t.surface.content == purple.surface.content);
    CHECK(t.text.primary == purple.text.primary);
    CHECK(t.nav.bg.lightnessF() < 0.1);
    // A filled grey control reads on white and carries white text.
    CHECK(t.accent.def.lightnessF() < 0.5);
    CHECK(t.accent.text.lightnessF() - t.accent.def.lightnessF() > 0.4);
    // The subtle accent plate is light, not the dark-mode grey.
    CHECK(t.accent.subtleBg.lightnessF() > 0.8);
}

TEST_CASE("buildTheme: pins are honoured, a light rail flips the ink", "[theme]") {
    Th::ChromeSpec spec;
    spec.rail            = QColor("#F5F0EB"); // Hoth-like light rail
    spec.pill            = QColor("#3F0E40");
    spec.pillInk         = QColor("#FFFFFF");
    spec.workspaceBubble = QColor("#DDD6CF");
    spec.accent          = {
        QColor("#4A154B"),
        QColor("#611F69"),
        QColor("#350D36"),
        QColor("#350D36"),
        QColor("#F4E5F5")
    };

    const Th::Theme light = Th::buildTheme(spec, false);
    // Derived ink on a light rail is dark.
    CHECK(light.nav.itemText.lightnessF() < 0.2);
    CHECK(light.nav.itemTextDim.lightnessF() < 0.5);
    CHECK(light.nav.scrollThumb.red() == 0);
    CHECK(light.nav.extBadgeText.lightnessF() < 0.5);
    CHECK(light.titleBar.controlHover == light.nav.itemText);
    // …and the content side is untouched.
    CHECK(light.surface.content == Th::defaultTheme().surface.content);
    // Dark content under the same light chrome keeps the chrome identical.
    const Th::Theme dark = Th::buildTheme(spec, true);
    CHECK(Th::isDarkTheme(dark));
    CHECK(dark.nav.itemText == light.nav.itemText);
    CHECK(dark.nav.bg == light.nav.bg);
    // The dark-content accent was lifted from the (dark) brand accent.
    CHECK(dark.accent.def.lightnessF() > light.accent.def.lightnessF());
    CHECK(qAbs(dark.accent.def.hslHueF() - light.accent.def.hslHueF()) < 0.02);

    // Pinned values survive derivation exactly.
    spec.itemHover       = QColor("#112233");
    spec.itemText        = QColor("#445566");
    spec.itemTextDim     = QColor("#778899");
    spec.presenceOnline  = QColor("#00FF00");
    spec.badgeMention    = QColor("#FF0000");
    spec.titleBarControl = QColor("#ABCDEF");
    spec.accentDark      = {
        QColor("#101010"),
        QColor("#202020"),
        QColor("#303030"),
        QColor("#404040"),
        QColor("#505050")
    };
    spec.iconAccentDark    = QColor("#606060");
    const Th::Theme pinned = Th::buildTheme(spec, true);
    CHECK(pinned.nav.itemHover == QColor("#112233"));
    CHECK(pinned.nav.itemText == QColor("#445566"));
    CHECK(pinned.nav.itemTextDim == QColor("#778899"));
    CHECK(pinned.presence.online == QColor("#00FF00"));
    CHECK(pinned.badge.mention == QColor("#FF0000"));
    CHECK(pinned.titleBar.controlDefault == QColor("#ABCDEF"));
    CHECK(pinned.accent.def == QColor("#101010"));
    CHECK(pinned.accent.subtleBg == QColor("#505050"));
    CHECK(pinned.icon.accent == QColor("#606060"));
    // Pins that only concern dark content don't leak into the light variant.
    const Th::Theme pinnedLight = Th::buildTheme(spec, false);
    CHECK(pinnedLight.accent.def == QColor("#4A154B"));
    CHECK(pinnedLight.icon.accent == QColor("#4A154B"));
}

TEST_CASE("ThemeManager switches, persists and ignores unknown ids", "[theme]") {
    auto &mgr = ThemeManager::instance();
    CHECK(mgr.themeId() == "purple"); // fresh settings → default

    QSignalSpy spy(&mgr, &ThemeManager::themeChanged);

    mgr.setThemeById("blue");
    CHECK(mgr.themeId() == "blue");
    CHECK(mgr.theme().nav.bg == Th::themeById("blue", false)->nav.bg);
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
    CHECK_FALSE(Th::isDarkTheme(*Th::themeById("purple", false)));
    CHECK(Th::isDarkTheme(*Th::themeById("purple", true)));
    CHECK_FALSE(Th::isDarkTheme(*Th::themeById("charcoal", false)));
    CHECK(Th::isDarkTheme(*Th::themeById("charcoal", true)));
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

    // Any preset fits either slot: the slot picks the chrome, the mode the
    // content. Editing the off-screen dark slot changes nothing on screen.
    mgr.setThemeIdFor(true, "blue");
    CHECK(mgr.themeIdFor(true) == "blue");
    CHECK(mgr.themeId() == "blue"); // the light slot, still on screen
    CHECK_FALSE(Th::isDarkTheme(mgr.theme()));
    CHECK(themeSpy.count() == 2);
    CHECK(QSettings("msga", "msga").value("appearance/themeDark").toString() == "blue");
    mgr.setThemeIdFor(true, "nope"); // unknown → ignored
    CHECK(mgr.themeIdFor(true) == "blue");
    mgr.setThemeIdFor(false, "charcoal"); // graphite chrome over light content
    CHECK(mgr.themeId() == "charcoal");
    CHECK_FALSE(Th::isDarkTheme(mgr.theme()));
    CHECK(mgr.theme().nav.bg == Th::themeById("charcoal", false)->nav.bg);
    CHECK(themeSpy.count() == 3);

    // Dark mode with the blue slot renders blue chrome over dark content.
    mgr.setMode(ThemeManager::ColorMode::Dark);
    CHECK(mgr.themeId() == "blue");
    CHECK(Th::isDarkTheme(mgr.theme()));
    CHECK(mgr.theme().nav.bg == Th::themeById("blue", true)->nav.bg);
    CHECK(themeSpy.count() == 4);
    mgr.setThemeIdFor(true, "charcoal");
    CHECK(themeSpy.count() == 5);
    mgr.setMode(ThemeManager::ColorMode::Light);
    CHECK(themeSpy.count() == 6);

    // setThemeById edits the slot on screen — the old single-slot API keeps
    // working for callers that don't know about modes.
    mgr.setThemeById("charcoal"); // light slot already charcoal → no-op
    CHECK(themeSpy.count() == 6);
    mgr.setThemeById("green");
    CHECK(mgr.themeId() == "green");
    CHECK(mgr.themeIdFor(false) == "green");
    CHECK(mgr.themeIdFor(true) == "charcoal");
    CHECK(themeSpy.count() == 7);

    // Same mode again is a no-op.
    mgr.setMode(ThemeManager::ColorMode::Light);
    CHECK(themeSpy.count() == 7);

    // Back to System (→ light here): nothing new on screen, but the mode
    // observers still hear about it.
    const int modeBefore = modeSpy.count();
    mgr.setMode(ThemeManager::ColorMode::System);
    CHECK(mgr.themeId() == "green");
    CHECK(themeSpy.count() == 7);
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

    for (const auto &info : Th::availableThemes())
        for (const auto *variant : {info.light, info.dark}) {
            INFO(
                "theme: " << info.id.toStdString()
                          << (Th::isDarkTheme(*variant) ? " dark" : " light")
            );
            ThemeManager::instance().setTheme(*variant);

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
