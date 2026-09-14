// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "media/audio_player.h"

#include <QFileInfo>
#include <QUrl>

namespace Media {

AudioPlayer &AudioPlayer::instance() {
    static AudioPlayer p;
    return p;
}

AudioPlayer::AudioPlayer() {
    _tick.setInterval(200);
    connect(&_tick, &QTimer::timeout, this, &AudioPlayer::tick);
}

void AudioPlayer::ensureEngine() {
    if (_engine)
        return;
    _engine = createPlatformEngine(this);
    bindEngine();
}

void AudioPlayer::setEngineForTesting(std::unique_ptr<Engine> engine) {
    stop();
    _engine = std::move(engine);
    if (_engine)
        bindEngine();
}

void AudioPlayer::bindEngine() {
    connect(_engine.get(), &Engine::loaded, this, [this] {
        if (_status.state != State::Loading)
            return;
        _engine->play();
        setState(State::Playing);
    });
    connect(_engine.get(), &Engine::failed, this, [this](const QString &err) {
        _status.error = err;
        setState(State::Error);
    });
    connect(_engine.get(), &Engine::ended, this, [this] {
        if (_status.state != State::Playing)
            return;
        if (const qint64 d = _engine->durationMs(); d > 0)
            _status.positionMs = d;
        setState(State::Ended);
    });
}

QString AudioPlayer::takeOver(const QString &key) {
    if (_status.key == key)
        return {};
    const QString prev = _status.key;
    if (_engine)
        _engine->stop();
    _tick.stop();
    _status = Status{.key = key};
    return prev;
}

void AudioPlayer::beginLoading(const QString &key, qint64 knownDurationMs) {
    const QString prev = takeOver(key);
    _knownDurationMs   = knownDurationMs;
    _status.durationMs = knownDurationMs;
    _status.positionMs = 0;
    _status.error.clear();
    _status.state = State::Loading;
    if (!prev.isEmpty())
        emit statusChanged(prev);
    emitChanged();
}

void AudioPlayer::loadFailed(const QString &key, const QString &error) {
    if (!isCurrent(key) || _status.state != State::Loading)
        return;
    _status.error = error;
    setState(State::Error);
}

void AudioPlayer::play(const QString &key, const QString &localPath, qint64 knownDurationMs) {
    if (isCurrent(key)) {
        if (_status.state == State::Playing)
            return;
        if (_status.state == State::Paused || _status.state == State::Ended) {
            resume();
            return;
        }
    }
    const QString prev = takeOver(key);
    ensureEngine();
    if (knownDurationMs > 0)
        _knownDurationMs = knownDurationMs;
    _status.durationMs = _knownDurationMs;
    _status.positionMs = 0;
    _status.error.clear();
    _status.state = State::Loading;
    if (!prev.isEmpty())
        emit statusChanged(prev);
    emitChanged();
    _engine->load(localPath);
}

void AudioPlayer::togglePause() {
    switch (_status.state) {
    case State::Playing:
        pause();
        break;
    case State::Paused:
    case State::Ended:
        resume();
        break;
    default:
        break;
    }
}

void AudioPlayer::pause() {
    if (_status.state != State::Playing || !_engine)
        return;
    _status.positionMs = _engine->positionMs();
    _engine->pause();
    setState(State::Paused);
}

void AudioPlayer::resume() {
    if (!_engine)
        return;
    if (_status.state == State::Ended) {
        _engine->seek(0);
        _status.positionMs = 0;
    } else if (_status.state != State::Paused) {
        return;
    }
    _engine->play();
    setState(State::Playing);
}

void AudioPlayer::seek(qint64 ms) {
    if (!_engine)
        return;
    if (_status.state != State::Playing && _status.state != State::Paused &&
        _status.state != State::Ended)
        return;
    const qint64 dur = _status.durationMs;
    ms               = std::max<qint64>(0, dur > 0 ? std::min(ms, dur) : ms);
    _engine->seek(ms);
    _status.positionMs = ms;
    if (_status.state == State::Ended) {
        _engine->play();
        setState(State::Playing);
    } else {
        emitChanged();
    }
}

void AudioPlayer::stop() {
    if (_status.key.isEmpty())
        return;
    const QString prev = _status.key;
    if (_engine)
        _engine->stop();
    _tick.stop();
    _status = Status{};
    emit statusChanged(prev);
}

void AudioPlayer::setState(State s) {
    _status.state = s;
    if (s == State::Playing)
        _tick.start();
    else
        _tick.stop();
    emitChanged();
}

void AudioPlayer::tick() {
    if (_status.state != State::Playing || !_engine)
        return;
    _status.positionMs = _engine->positionMs();
    emitChanged();
}

void AudioPlayer::emitChanged() {
    if (_engine && _status.state != State::Idle && _status.state != State::Loading) {
        if (const qint64 d = _engine->durationMs(); d > 0)
            _status.durationMs = d;
        else if (_knownDurationMs > 0)
            _status.durationMs = _knownDurationMs;
    }
    if (_status.durationMs > 0)
        _status.positionMs = std::clamp<qint64>(_status.positionMs, 0, _status.durationMs);
    emit statusChanged(_status.key);
}

QString AudioPlayer::extensionOf(const QString &nameOrUrl) {
    QString path = nameOrUrl;
    if (path.contains(QLatin1String("://")))
        path = QUrl(path).path();
    const QString ext = QFileInfo(path).suffix().toLower();
    return ext;
}

QString AudioPlayer::sourceUrlFor(const File &f) const {
    const_cast<AudioPlayer *>(this)->ensureEngine();
    for (const QString &url : {f.urlPrivate, f.urlPrivateDownload, f.aacUrl}) {
        if (url.isEmpty())
            continue;
        QString ext = extensionOf(url);
        if (ext.isEmpty())
            ext = extensionOf(f.name);
        if (_engine->supportsExtension(ext))
            return url;
    }
    return f.urlPrivate;
}

} // namespace Media
