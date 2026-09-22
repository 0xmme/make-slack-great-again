// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include "ui/app_dialog/app_dialog.h"

#include <QImage>
#include <QPixmap>

class QLabel;
class StyledButton;

// "Workspace icon": pick a picture that only this install shows for a
// workspace (a non-admin cannot change the one Slack serves). The card
// previews the rail bubble with the candidate, or the letter fallback after
// "Use default". Pictures come from a file chooser or a drop onto the card.
//
//   teamId/name — drive the bubble colour and the letter fallback
//   current     — the icon the rail shows now (null = letter fallback)
//   hasCustom   — whether an override is already installed (enables "Use default")
//
// After exec()/finished() == Accepted, exactly one holds:
//   resetRequested()        — remove the override, show the server icon again
//   !chosenImage().isNull() — install this picture (already bounded, not yet cropped)
// The dialog changes nothing itself; the caller applies the result.
class WorkspaceIconDialog : public AppDialog {
    Q_OBJECT
public:
    WorkspaceIconDialog(
        const QString &teamId,
        const QString &name,
        const QPixmap &current,
        bool           hasCustom,
        QWidget       *parent = nullptr
    );

    QImage chosenImage() const { return _chosen; }
    bool   resetRequested() const { return _reset; }

    // Decode `path` into the preview. False (and the preview unchanged) when
    // the file is not an image we can read.
    bool loadFile(const QString &path);
    // Same for pixels already in memory (a dropped/pasted picture).
    bool loadImage(const QImage &img);

protected:
    void applyTheme() override;
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dropEvent(QDropEvent *e) override;

private:
    class Preview;

    void chooseFile();
    void useDefault();
    void refreshButtons();

    QString _teamId;
    QString _name;
    QPixmap _current;
    bool    _hasCustom = false;
    QImage  _chosen; // null until a picture is loaded
    bool    _reset = false;
    bool    _dirty = false; // something to save

    Preview      *_preview    = nullptr;
    QLabel       *_hint       = nullptr;
    StyledButton *_chooseBtn  = nullptr;
    StyledButton *_defaultBtn = nullptr;
    StyledButton *_saveBtn    = nullptr;
    StyledButton *_cancelBtn  = nullptr;
};
