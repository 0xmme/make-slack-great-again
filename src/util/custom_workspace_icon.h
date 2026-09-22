// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include "backend/domain.h"

#include <QImage>
#include <QString>

// Files behind TokenStore's custom workspace icon: the user's picture is
// normalised into a small square PNG the app owns under its data dir, so the
// original may move or vanish without the rail losing the icon. Each install
// writes a NEW file name (and deletes the previous one) so the file:// URL the
// ImageCache keys on changes with the picture — a same-name overwrite would
// keep serving the stale decoded pixmap.
namespace CustomWorkspaceIcon {

// Longest side of a stored icon. The rail paints 40 logical px; 256 leaves
// headroom for any DPR and for the quick switcher without storing a photo.
constexpr int kStoredSize = 256;

// Centre-crop to a square and shrink to at most kStoredSize (never upscaled).
// Null in → null out. Pure; what install() writes and the dialog previews.
QImage prepare(const QImage &src);

// Normalise `src`, write it under the app data dir, point TokenStore at it and
// drop the icon that was there before. Returns the stored file path, empty on
// failure (nothing is changed then).
QString install(const WorkspaceKey &key, const QImage &src);

// Remove the override (setting + file); the server icon shows again.
void remove(const WorkspaceKey &key);

// Directory the icons live in (created on demand by install()).
QString directory();

} // namespace CustomWorkspaceIcon
