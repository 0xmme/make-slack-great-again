// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "media/audio_engine.h"

#import <AVFoundation/AVFoundation.h>

#include <QCoreApplication>
#include <QStringList>

// macOS: AVAudioPlayer — pause/seek/position built in, decodes MP3, AAC/M4A,
// WAV, AIFF, FLAC, CAF natively. Delegate callbacks land on the main thread.
// Manual retain/release (no ARC), like the other .mm files in this tree.

namespace Media {
namespace {
} // namespace
} // namespace Media

@interface MsgaAudioPlayerDelegate : NSObject <AVAudioPlayerDelegate>
@property(nonatomic, assign) Media::Engine *engine;
@end

@implementation MsgaAudioPlayerDelegate
- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag {
    (void)player;
    if (!self.engine)
        return;
    if (flag)
        emit self.engine->ended();
    else
        emit self.engine->failed(QCoreApplication::translate("Media::AudioPlayer", "Audio playback failed"));
}
- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError *)error {
    (void)player;
    if (!self.engine)
        return;
    emit self.engine->failed(
        error ? QString::fromNSString(error.localizedDescription)
              : QCoreApplication::translate("Media::AudioPlayer", "Audio playback failed")
    );
}
@end

namespace Media {
namespace {

class MacEngine : public Engine {
public:
    using Engine::Engine;
    ~MacEngine() override { stop(); }

    void load(const QString &path) override {
        stop();
        NSURL   *url = [NSURL fileURLWithPath:path.toNSString()];
        NSError *err = nil;
        _player      = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&err];
        if (!_player) {
            emit failed(
                err ? QString::fromNSString(err.localizedDescription)
                    : QCoreApplication::translate("Media::AudioPlayer", "This audio format can't be played here")
            );
            return;
        }
        _delegate        = [[MsgaAudioPlayerDelegate alloc] init];
        _delegate.engine = this;
        _player.delegate = _delegate;
        [_player prepareToPlay];
        emit loaded();
    }

    void play() override {
        if (_player)
            [_player play];
    }
    void pause() override {
        if (_player)
            [_player pause];
    }
    void seek(qint64 ms) override {
        if (_player)
            _player.currentTime = ms / 1000.0;
    }
    void stop() override {
        if (_player) {
            [_player stop];
            _player.delegate = nil;
            [_player release];
            _player = nil;
        }
        if (_delegate) {
            _delegate.engine = nullptr;
            [_delegate release];
            _delegate = nil;
        }
    }

    qint64 positionMs() const override {
        return _player ? (qint64)(_player.currentTime * 1000.0) : 0;
    }
    qint64 durationMs() const override {
        return _player ? (qint64)(_player.duration * 1000.0) : 0;
    }

    bool supportsExtension(const QString &ext) const override {
        static const QStringList k{"mp3", "m4a", "mp4", "aac", "wav", "aif", "aiff", "flac",
                                   "caf", "alac"};
        return k.contains(ext);
    }

private:
    AVAudioPlayer           *_player   = nil;
    MsgaAudioPlayerDelegate *_delegate = nil;
};

} // namespace

std::unique_ptr<Engine> createPlatformEngine(QObject *parent) {
    return std::make_unique<MacEngine>(parent);
}

} // namespace Media
