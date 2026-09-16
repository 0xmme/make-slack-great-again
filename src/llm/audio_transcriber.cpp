// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "audio_transcriber.h"

#include "llm_service.h"

AudioTranscriber &AudioTranscriber::instance() {
    static AudioTranscriber t;
    return t;
}

std::optional<QString> AudioTranscriber::cached(const QString &fileId) const {
    const auto it = _done.constFind(fileId);
    if (it == _done.constEnd())
        return std::nullopt;
    return *it;
}

bool AudioTranscriber::inFlight(const QString &fileId) const {
    return _pending.contains(fileId);
}

void AudioTranscriber::transcribe(
    const QString                     &fileId,
    LlmWire::TranscriptionInput        in,
    std::function<void(QString text)>  onText,
    std::function<void(QString error)> onError,
    QObject                           *ctx
) {
    if (const auto hit = cached(fileId)) {
        if (onText)
            onText(*hit);
        return;
    }
    const bool alreadyRunning = _pending.contains(fileId);
    _pending[fileId].push_back({QPointer<QObject>(ctx), std::move(onText), std::move(onError)});
    if (alreadyRunning)
        return;
    emit stateChanged(fileId);

    // Settle every listener registered while the request ran, then forget the
    // key. A listener whose context died is skipped; the result is still
    // cached for the next click.
    auto settle = [this, fileId](std::optional<QString> text, QString error) {
        const std::vector<Listener> listeners = _pending.take(fileId);
        if (text)
            _done.insert(fileId, *text);
        emit stateChanged(fileId);
        for (const auto &l : listeners) {
            if (!l.ctx)
                continue;
            if (text) {
                if (l.onText)
                    l.onText(*text);
            } else if (l.onError) {
                l.onError(error);
            }
        }
    };
    LlmService::instance().transcribe(
        std::move(in),
        [settle](QString text) { settle(std::move(text), {}); },
        [settle](QString error) { settle(std::nullopt, std::move(error)); }
    );
}

void AudioTranscriber::clearCache() {
    _done.clear();
}
