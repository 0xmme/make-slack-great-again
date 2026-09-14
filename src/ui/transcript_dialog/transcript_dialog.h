// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include "ui/app_dialog/app_dialog.h"
#include "ui/message_list/message_render.h"

#include <vector>

class QLabel;
class QScrollArea;
class StyledButton;

// "Transcript (auto-generated)" — Slack's own speech-to-text for a voice clip
// (files.info `transcription` + the WebVTT at `vtt`), shown as timestamped
// lines under an "Author at time" subtitle. Opens in the Loading shape; the
// host fills it with setCues() once the VTT is downloaded (or setText() with
// the one-line preview when the download fails).
class TranscriptDialog : public AppDialog {
    Q_OBJECT
public:
    explicit TranscriptDialog(const QString &subtitle, QWidget *parent = nullptr);

    void setCues(const std::vector<MsgRender::VttCue> &cues);
    void setText(const QString &text); // single cue at 0:00
    void setFailed(const QString &error);

protected:
    void applyTheme() override;

private:
    QLabel       *_subtitle = nullptr;
    QLabel       *_body     = nullptr;
    QScrollArea  *_scroll   = nullptr;
    StyledButton *_copyBtn  = nullptr;
    QString       _plain; // what Copy puts on the clipboard
};
