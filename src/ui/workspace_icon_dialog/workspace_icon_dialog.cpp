// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "workspace_icon_dialog.h"
#include "ui/file_dialog_utils.h"
#include "ui/image_cache.h"
#include "ui/styled_button/styled_button.h"
#include "ui/theme.h"
#include "ui/workspace_switcher/workspace_bubble.h"
#include "util/custom_workspace_icon.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QMimeData>
#include <QPainter>
#include <QPushButton>
#include <QUrl>
#include <QVBoxLayout>

namespace {
// Preview bubble: bigger than the rail's 40 px so the crop is judgeable, with
// the corner radius scaled to keep the rail's shape.
constexpr int kPreviewSize   = 96;
constexpr int kPreviewRadius = 24;
} // namespace

// The rail bubble at preview size, painted through the same routine the rail
// uses so what the user approves is what the rail will show.
class WorkspaceIconDialog::Preview : public QWidget {
public:
    explicit Preview(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(kPreviewSize, kPreviewSize);
    }
    void setBubble(const QString &teamId, const QString &name) {
        _teamId = teamId;
        _name   = name;
        update();
    }
    void setIcon(const QPixmap &icon) {
        _icon = icon;
        update();
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.setRenderHint(QPainter::SmoothPixmapTransform);
        // Scaled per paint (cheap at this size) so a DPR change never shows a
        // pixmap baked for the previous screen.
        const QPixmap scaled =
            _icon.isNull() ? QPixmap()
                           : Ui::scaleWorkspaceIcon(_icon, kPreviewSize, devicePixelRatioF());
        Ui::paintWorkspaceBubble(
            p,
            QRectF(rect()),
            {.teamId = _teamId, .name = _name, .icon = scaled, .radius = kPreviewRadius},
            font()
        );
    }

private:
    QString _teamId;
    QString _name;
    QPixmap _icon;
};

WorkspaceIconDialog::WorkspaceIconDialog(
    const QString &teamId,
    const QString &name,
    const QPixmap &current,
    bool           hasCustom,
    QWidget       *parent
)
    : AppDialog(tr("Workspace icon"), parent), _teamId(teamId), _name(name), _current(current),
      _hasCustom(hasCustom) {
    setAcceptDrops(true);

    auto       *cl = contentLayout();
    const auto &sp = Th::c().spacing;
    cl->setSpacing(sp.md);

    _preview = new Preview;
    _preview->setBubble(teamId, name);
    _preview->setIcon(current);
    cl->addWidget(_preview, 0, Qt::AlignHCenter);

    _chooseBtn = new StyledButton(tr("Choose image…"), StyledButton::Variant::Secondary);
    connect(_chooseBtn, &QPushButton::clicked, this, &WorkspaceIconDialog::chooseFile);
    cl->addWidget(_chooseBtn, 0, Qt::AlignHCenter);

    _hint = new QLabel(
        tr("Only you see this icon. The picture is cropped to a square. You can also drop an "
           "image file onto this window.")
    );
    _hint->setWordWrap(true);
    _hint->setAlignment(Qt::AlignHCenter);
    cl->addWidget(_hint);

    _defaultBtn = new StyledButton(tr("Use default"), StyledButton::Variant::Ghost);
    connect(_defaultBtn, &QPushButton::clicked, this, &WorkspaceIconDialog::useDefault);
    _cancelBtn = new StyledButton(tr("Cancel"), StyledButton::Variant::Secondary);
    _saveBtn   = new StyledButton(tr("Save"), StyledButton::Variant::Primary);
    addButtonRow(_saveBtn, _cancelBtn, _defaultBtn); // Cancel → reject() wired by base
    connect(_saveBtn, &QPushButton::clicked, this, [this] {
        if (_dirty)
            accept();
    });

    refreshButtons();
    applyTheme();
    updateCard();
}

bool WorkspaceIconDialog::loadFile(const QString &path) {
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly))
        return false;
    // The cache decoder handles every format the app shows (raster + SVG) and
    // bounds the decode, so a 20-megapixel photo never lands in memory whole.
    return loadImage(ImageCache::decodeBoundedImage(f.readAll(), CustomWorkspaceIcon::kStoredSize));
}

bool WorkspaceIconDialog::loadImage(const QImage &img) {
    if (img.isNull())
        return false;
    _chosen = img;
    _reset  = false;
    _dirty  = true;
    _preview->setIcon(QPixmap::fromImage(CustomWorkspaceIcon::prepare(img)));
    refreshButtons();
    return true;
}

void WorkspaceIconDialog::chooseFile() {
    const QString path = Ui::getOpenFileName(
        this,
        tr("Choose workspace icon"),
        tr("Images (*.png *.jpg *.jpeg *.webp *.gif *.bmp *.svg)")
    );
    if (path.isEmpty())
        return;
    if (!loadFile(path))
        _hint->setText(tr("That file could not be read as an image."));
}

void WorkspaceIconDialog::useDefault() {
    _chosen = {};
    _reset  = true;
    _dirty  = _hasCustom; // nothing to save when no override exists
    _preview->setIcon({});
    refreshButtons();
}

void WorkspaceIconDialog::refreshButtons() {
    _saveBtn->setEnabled(_dirty);
    // Offered while an override is installed or a new picture is pending —
    // either way there is something to fall back from.
    _defaultBtn->setVisible(_hasCustom || !_chosen.isNull());
    _defaultBtn->setEnabled(!_reset);
}

void WorkspaceIconDialog::applyTheme() {
    AppDialog::applyTheme();
    if (_hint)
        _hint->setStyleSheet(QString("color: %1; font-size: %2px;")
                                 .arg(Th::qss(Th::c().text.secondary))
                                 .arg(Th::c().fonts.sm));
}

static QString droppedImagePath(const QMimeData *mime) {
    if (!mime || !mime->hasUrls())
        return {};
    for (const QUrl &u : mime->urls())
        if (u.isLocalFile())
            return u.toLocalFile();
    return {};
}

void WorkspaceIconDialog::dragEnterEvent(QDragEnterEvent *e) {
    const auto *mime = e->mimeData();
    if (mime && (mime->hasImage() || !droppedImagePath(mime).isEmpty()))
        e->acceptProposedAction();
}

void WorkspaceIconDialog::dropEvent(QDropEvent *e) {
    const auto *mime = e->mimeData();
    bool        ok   = false;
    if (const QString path = droppedImagePath(mime); !path.isEmpty())
        ok = loadFile(path);
    else if (mime && mime->hasImage())
        ok = loadImage(qvariant_cast<QImage>(mime->imageData()));
    if (ok)
        e->acceptProposedAction();
    else
        _hint->setText(tr("That file could not be read as an image."));
}
