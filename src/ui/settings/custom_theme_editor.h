// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include "ui/theme_custom.h"

#include <QWidget>

class QCheckBox;
class QLabel;
class StyledButton;
class StyledLineEdit;

// Settings → Appearance → Custom theme. The theme itself comes from Slack: an
// import field (legacy 8/10-hex share string or `ia_theme` JSON) and "Use my
// Slack theme"; below them the darker-sidebar and gradient switches, and
// "Copy theme" for the way back. Every discrete edit emits themeEdited with
// the complete definition; the owner applies it through
// ThemeManager::setCustomTheme (which is what re-renders the app).
class CustomThemeEditor : public QWidget {
    Q_OBJECT
public:
    explicit CustomThemeEditor(QWidget *parent = nullptr);

    // Load a definition into the controls without emitting themeEdited.
    void            setTheme(const Th::CustomTheme &t);
    Th::CustomTheme theme() const { return _theme; }

    // Whether any workspace can serve the user's Slack theme (shows the button).
    void setSlackThemeAvailable(bool on);
    // Inline status under the buttons (import errors, "Copied", fetch results).
    void showStatus(const QString &text, bool error);

    // Restyle for the active theme; call on ThemeManager::themeChanged.
    void applyTheme();

signals:
    void themeEdited(const Th::CustomTheme &theme);
    void slackThemeRequested();

private:
    void syncControls(); // controls ← _theme (no signals)
    void refreshContrast();
    void importText();
    void copyTheme();
    void emitEdited();

    Th::CustomTheme _theme;
    StyledLineEdit *_import      = nullptr;
    StyledButton   *_importBtn   = nullptr;
    QCheckBox      *_inverted    = nullptr;
    QCheckBox      *_gradient    = nullptr;
    QLabel         *_contrast    = nullptr;
    StyledButton   *_copyBtn     = nullptr;
    StyledButton   *_slackBtn    = nullptr;
    QLabel         *_status      = nullptr;
    bool            _statusError = false;
    bool            _syncing     = false; // suppress edits while loading
};
