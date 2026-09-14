/* Single translation unit for the vendored miniaudio decoder (public domain /
 * MIT-0, see LICENSE). Decoding only: MP3 (dr_mp3), WAV (dr_wav), FLAC
 * (dr_flac) and Ogg Vorbis (stb_vorbis). Device I/O is compiled out — the
 * static Linux release binary can't dlopen a sound server, so playback goes
 * through a helper process instead (src/media/audio_engine_linux.cpp). */
#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"

#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_DEVICE_IO
#define MA_NO_THREADING
#define MA_NO_ENCODING
#define MA_NO_GENERATION
#define MA_NO_RESOURCE_MANAGER
#define MA_NO_NODE_GRAPH
#define MA_NO_ENGINE
#include "miniaudio.h"

/* stb_vorbis implementation, after miniaudio so ma_dr_* symbols don't clash. */
#undef STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"
