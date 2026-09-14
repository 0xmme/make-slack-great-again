// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include <QObject>
#include <QString>
#include <memory>

namespace Media {

// Platform playback engine behind AudioPlayer: one local file at a time, with
// pause/seek/position. Every call is main-thread; results arrive as signals on
// the main thread too. Backends (see audio_engine_{linux,mac,win}):
//   • Linux   — in-process decode (miniaudio: MP3/WAV/FLAC/Vorbis; `ffmpeg` on
//               PATH for the rest) piped as raw PCM into the desktop's sound
//               server helper (pw-cat / paplay / aplay). No shared-lib deps,
//               so the fully static release binary keeps working.
//   • macOS   — AVAudioPlayer (AVFoundation).
//   • Windows — MFPlay (Media Foundation).
class Engine : public QObject {
    Q_OBJECT
public:
    using QObject::QObject;

    // Start loading `path`, replacing any current media. Emits loaded() once
    // play() may be called (duration known where the backend can tell), or
    // failed(). A load may complete synchronously — connect before calling.
    virtual void load(const QString &path) = 0;
    virtual void play()                    = 0; // start, or resume after pause()
    virtual void pause()                   = 0;
    virtual void seek(qint64 ms)           = 0;
    virtual void stop()                    = 0; // release the media

    virtual qint64 positionMs() const = 0;
    virtual qint64 durationMs() const = 0; // 0 = unknown

    // Whether this backend can decode a file with this lower-case extension
    // ("mp3", "m4a", …). Drives AudioPlayer::sourceUrlFor.
    virtual bool supportsExtension(const QString &ext) const = 0;

signals:
    void loaded();
    void failed(QString error);
    void ended();
};

// The engine for the platform this binary was built for.
std::unique_ptr<Engine> createPlatformEngine(QObject *parent);

} // namespace Media
