// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "media/audio_engine.h"

#include <QCoreApplication>
#include <QDir>
#include <QMetaObject>
#include <QStringList>
#include <atomic>
#include <string>

#include <windows.h>
// Media Foundation headers must follow <windows.h>.
#include <mfapi.h>
#include <mfplay.h>
#include <mferror.h>
#include <propidl.h>

// Windows: MFPlay (Media Foundation's ready-made player). Deprecated in the
// docs but shipped by every Windows 7+ install, and the only MF surface with
// play/pause/seek/position in a few calls. Decodes MP3, AAC/M4A, WAV, WMA,
// FLAC natively. Events arrive on an MF worker thread; each is marshalled to
// the Qt thread with a generation stamp so a late event from a replaced media
// item can't touch the new one.

namespace Media {
namespace {

class WinEngine : public Engine, public IMFPMediaPlayerCallback {
public:
    using Engine::Engine;
    ~WinEngine() override { stop(); }

    void load(const QString &path) override {
        stop();
        const int gen = ++_generation;
        HRESULT   hr  = MFPCreateMediaPlayer(
            nullptr, FALSE, MFP_OPTION_FREE_THREADED_CALLBACK, this, nullptr, &_player
        );
        if (FAILED(hr) || !_player) {
            _player = nullptr;
            emit failed(
                QCoreApplication::translate("Media::AudioPlayer", "Audio playback is unavailable")
            );
            return;
        }
        const std::wstring w = QDir::toNativeSeparators(path).toStdWString();
        hr = _player->CreateMediaItemFromURL(w.c_str(), FALSE, (DWORD_PTR)gen, nullptr);
        if (FAILED(hr))
            emit failed(
                QCoreApplication::translate(
                    "Media::AudioPlayer", "This audio format can't be played here"
                )
            );
    }

    void play() override {
        if (_player)
            _player->Play();
    }
    void pause() override {
        if (_player)
            _player->Pause();
    }
    void seek(qint64 ms) override {
        if (!_player)
            return;
        PROPVARIANT v;
        PropVariantInit(&v);
        v.vt            = VT_I8;
        v.hVal.QuadPart = ms * 10000;
        _player->SetPosition(MFP_POSITIONTYPE_100NS, &v);
        PropVariantClear(&v);
    }
    void stop() override {
        ++_generation;
        if (!_player)
            return;
        IMFPMediaPlayer *p = _player;
        _player            = nullptr;
        p->Shutdown();
        p->Release();
    }

    qint64 positionMs() const override { return query(&IMFPMediaPlayer::GetPosition); }
    qint64 durationMs() const override { return query(&IMFPMediaPlayer::GetDuration); }

    bool supportsExtension(const QString &ext) const override {
        static const QStringList k{
            "mp3", "m4a", "mp4", "aac", "adts", "wav", "wma", "flac", "aif", "aiff"
        };
        return k.contains(ext);
    }

    // ── IUnknown: lifetime is the QObject's, so Release never deletes ────────
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv) override {
        if (!ppv)
            return E_POINTER;
        if (riid == __uuidof(IUnknown) || riid == __uuidof(IMFPMediaPlayerCallback)) {
            *ppv = static_cast<IMFPMediaPlayerCallback *>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }
    STDMETHODIMP_(ULONG) AddRef() override { return InterlockedIncrement(&_ref); }
    STDMETHODIMP_(ULONG) Release() override { return InterlockedDecrement(&_ref); }

    // ── IMFPMediaPlayerCallback (MF worker thread) ───────────────────────────
    void STDMETHODCALLTYPE OnMediaPlayerEvent(MFP_EVENT_HEADER *h) override {
        if (!h)
            return;
        const int gen = _generation.load();
        switch (h->eEventType) {
        case MFP_EVENT_TYPE_MEDIAITEM_CREATED: {
            if (FAILED(h->hrEvent)) {
                post(gen, [this] {
                    emit failed(
                        QCoreApplication::translate(
                            "Media::AudioPlayer", "This audio format can't be played here"
                        )
                    );
                });
                return;
            }
            auto *e = MFP_GET_MEDIAITEM_CREATED_EVENT(h);
            if (e->pMediaItem && h->pMediaPlayer && (int)e->dwUserData == gen)
                h->pMediaPlayer->SetMediaItem(e->pMediaItem);
            break;
        }
        case MFP_EVENT_TYPE_MEDIAITEM_SET:
            post(gen, [this, ok = SUCCEEDED(h->hrEvent)] {
                if (ok)
                    emit loaded();
                else
                    emit failed(
                        QCoreApplication::translate(
                            "Media::AudioPlayer", "This audio format can't be played here"
                        )
                    );
            });
            break;
        case MFP_EVENT_TYPE_PLAYBACK_ENDED:
            post(gen, [this] { emit ended(); });
            break;
        case MFP_EVENT_TYPE_ERROR:
            post(gen, [this] {
                emit failed(
                    QCoreApplication::translate("Media::AudioPlayer", "Audio playback failed")
                );
            });
            break;
        default:
            break;
        }
    }

private:
    template <class F>
    void post(int gen, F &&f) {
        QMetaObject::invokeMethod(
            this,
            [this, gen, fn = std::forward<F>(f)] {
                if (gen == _generation.load())
                    fn();
            },
            Qt::QueuedConnection
        );
    }

    qint64 query(HRESULT (STDMETHODCALLTYPE IMFPMediaPlayer::*fn)(REFGUID, PROPVARIANT *)) const {
        if (!_player)
            return 0;
        PROPVARIANT v;
        PropVariantInit(&v);
        qint64 ms = 0;
        if (SUCCEEDED((_player->*fn)(MFP_POSITIONTYPE_100NS, &v)) && v.vt == VT_I8)
            ms = v.hVal.QuadPart / 10000;
        PropVariantClear(&v);
        return ms;
    }

    IMFPMediaPlayer *_player = nullptr;
    LONG             _ref    = 1;
    std::atomic<int> _generation{0};
};

} // namespace

std::unique_ptr<Engine> createPlatformEngine(QObject *parent) {
    return std::make_unique<WinEngine>(parent);
}

} // namespace Media
