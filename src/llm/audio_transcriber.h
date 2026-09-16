// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
// App-wide speech-to-text of audio attachments through the AI layer — the
// "Transcribe" button on the inline audio player. Sits between the message
// lists (several of them show the same file: channel, thread panel, search)
// and LlmService::transcribe(): one request per file however many chips ask,
// and the result is kept for the session so a second look costs nothing.
//
// The transcriber never touches Slack: the caller has the bytes (the same
// download the player uses) and hands them over. Callbacks fire on the GUI
// thread and are dropped once `ctx` is gone.
#pragma once

#include "llm_wire.h"

#include <QHash>
#include <QObject>
#include <QPointer>
#include <QSet>
#include <QString>
#include <functional>
#include <optional>
#include <vector>

class AudioTranscriber : public QObject {
    Q_OBJECT
public:
    static AudioTranscriber &instance();

    // The finished transcript of `fileId`, if this session produced one.
    [[nodiscard]] std::optional<QString> cached(const QString &fileId) const;
    // A request for `fileId` is on the wire (the chip paints its button busy).
    [[nodiscard]] bool                   inFlight(const QString &fileId) const;

    // Transcribe `in.audio` as `fileId`. A cached transcript answers at once
    // (synchronously); an in-flight request just gains another listener.
    // Exactly one of onText/onError fires, unless `ctx` dies first.
    void transcribe(
        const QString                     &fileId,
        LlmWire::TranscriptionInput        in,
        std::function<void(QString text)>  onText,
        std::function<void(QString error)> onError,
        QObject                           *ctx
    );

    // Tests: drop every cached transcript.
    void clearCache();

signals:
    // `fileId` started or finished (either way) — repaint its chips.
    void stateChanged(QString fileId);

private:
    AudioTranscriber() = default;

    struct Listener {
        QPointer<QObject>                  ctx;
        std::function<void(QString text)>  onText;
        std::function<void(QString error)> onError;
    };

    QHash<QString, QString>               _done;
    QHash<QString, std::vector<Listener>> _pending; // keys = in-flight file ids
};
