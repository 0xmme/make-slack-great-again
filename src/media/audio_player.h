// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include "backend/domain.h"
#include "media/audio_engine.h"

#include <QObject>
#include <QString>
#include <QTimer>
#include <memory>

namespace Media {

// App-wide inline audio playback (the audio file chips in the message list).
// One file plays at a time; playback continues across conversation switches,
// and every message list paints the same status for the same file key, so a
// chip in the thread panel and the same chip in the channel agree.
//
// The player never touches the network: the UI downloads the bytes (auth
// headers) into the on-disk cache, marking the key as Loading meanwhile, and
// hands the local path to play(). Durations from Slack (`duration_ms`) are
// shown until the engine knows better.
class AudioPlayer : public QObject {
    Q_OBJECT
public:
    enum class State { Idle, Loading, Playing, Paused, Ended, Error };

    struct Status {
        QString key; // file id; empty when nothing is loaded
        State   state      = State::Idle;
        qint64  positionMs = 0;
        qint64  durationMs = 0; // 0 = unknown
        QString error;          // State::Error only
    };

    static AudioPlayer &instance();

    const Status &status() const { return _status; }
    bool isCurrent(const QString &key) const { return !key.isEmpty() && _status.key == key; }

    // The UI is fetching the bytes: paint the chip as loading. A later play() or
    // loadFailed() for the same key resolves it; a different key supersedes it.
    void beginLoading(const QString &key, qint64 knownDurationMs);
    void loadFailed(const QString &key, const QString &error);

    // Load the local file and start playing it. Same key while paused = resume.
    void play(const QString &key, const QString &localPath, qint64 knownDurationMs = 0);
    void togglePause(); // Playing → pause; Paused/Ended → resume (Ended restarts)
    void pause();
    void resume();
    void seek(qint64 ms);
    void stop();

    // Which of the file's URLs to fetch for playback: the first of url_private,
    // the original upload (url_private_download) and Slack's AAC transcode
    // whose extension the platform engine can decode; url_private otherwise.
    // (For audio uploads url_private already IS the AAC transcode — the
    // original .mp3/.wav is what a Linux build without ffmpeg can play.)
    QString        sourceUrlFor(const File &f) const;
    // Lower-case extension of a file name or URL path ("mp3"), empty if none.
    static QString extensionOf(const QString &nameOrUrl);

    // Tests swap in a scripted engine.
    void setEngineForTesting(std::unique_ptr<Engine> engine);

signals:
    // Anything about `key` changed (state, position, duration). Fired for the
    // previous key too when another file takes over, so both chips repaint.
    void statusChanged(QString key);

private:
    AudioPlayer();
    void    ensureEngine();
    void    bindEngine();
    void    setState(State s);
    void    tick();
    void    emitChanged();
    QString takeOver(const QString &key); // returns the previous key (if different)

    std::unique_ptr<Engine> _engine;
    Status                  _status;
    qint64                  _knownDurationMs = 0;
    QTimer                  _tick;
};

} // namespace Media
