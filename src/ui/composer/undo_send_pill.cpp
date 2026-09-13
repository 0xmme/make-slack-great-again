// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "undo_send_pill.h"
#include "ui/paint_utils.h"
#include "ui/shortcuts.h"
#include "ui/theme.h"
#include "ui/theme_manager.h"

#include <QFontMetrics>
#include <QMouseEvent>
#include <QPainter>

UndoSendPill::UndoSendPill(QWidget *parent) : QWidget(parent) {
    setObjectName("undoSendPill");
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::NoFocus);
    hide();
    connect(&ThemeManager::instance(), &ThemeManager::themeChanged, this, [this] { update(); });
}

QString UndoSendPill::sentText() const {
    return tr("Message sent");
}

QString UndoSendPill::undoText() const {
    return tr("Undo");
}

QString UndoSendPill::hintText() const {
    return Ui::Shortcuts::nativeKeys(Ui::Shortcut::UndoSend);
}

QSize UndoSendPill::chipSize() const {
    QFont f = font();
    f.setPixelSize(Th::c().fonts.caption);
    QFont bold = f;
    bold.setBold(true);
    const QFontMetrics fm(f), bfm(bold);
    const int w = kPadH + fm.horizontalAdvance(sentText()) + kGapDot + fm.horizontalAdvance(u'·') +
                  kGapDot + bfm.horizontalAdvance(undoText()) + fm.horizontalAdvance(' ') +
                  fm.horizontalAdvance(hintText()) + kPadH;
    const int h = kPadV + fm.height() + kPadV;
    return {w + 2 * kShadow, h + 2 * kShadow};
}

void UndoSendPill::showAbove(const QRect &anchorGlobalRect) {
    // Float above every sibling of the top-level window: the construction parent
    // (the composer) would clip a chip that sticks out above its own top edge.
    QWidget *host = parentWidget() ? parentWidget()->window() : nullptr;
    if (host && parentWidget() != host)
        setParent(host);

    const QSize  sz = chipSize();
    const QPoint globalTopLeft(
        anchorGlobalRect.right() - sz.width() + kShadow,
        anchorGlobalRect.top() - sz.height() + kShadow - kGap
    );
    const bool  wasVisible = isVisible();
    const QRect oldGeom    = geometry();
    setFixedSize(sz);
    move(host ? host->mapFromGlobal(globalTopLeft) : globalTopLeft);
    if (wasVisible && parentWidget())
        parentWidget()->update(oldGeom.united(geometry()));
    show();
    raise();
    update();
}

void UndoSendPill::hideEvent(QHideEvent *e) {
    if (QWidget *p = parentWidget())
        p->update(geometry());
    QWidget::hideEvent(e);
}

void UndoSendPill::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        e->accept();
        emit undoClicked();
        return;
    }
    QWidget::mousePressEvent(e);
}

void UndoSendPill::enterEvent(QEnterEvent *e) {
    _hover = true;
    update();
    QWidget::enterEvent(e);
}

void UndoSendPill::leaveEvent(QEvent *e) {
    _hover = false;
    update();
    QWidget::leaveEvent(e);
}

void UndoSendPill::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const auto  &th = Th::c();
    const QRectF body(kShadow, kShadow, width() - 2 * kShadow, height() - 2 * kShadow);
    Paint::dropShadow(p, body, kRadius, kShadow, 0, 3);
    p.setPen(Qt::NoPen);
    p.setBrush(th.tooltip.bg);
    p.drawRoundedRect(body, kRadius, kRadius);

    QFont f = font();
    f.setPixelSize(th.fonts.caption);
    QFont bold = f;
    bold.setBold(true);
    bold.setUnderline(_hover);
    const QFontMetrics fm(f);

    qreal       x        = body.left() + kPadH;
    const qreal baseline = body.top() + kPadV + fm.ascent();
    const auto  draw     = [&](const QString &text, const QFont &font, const QColor &color) {
        p.setFont(font);
        p.setPen(color);
        p.drawText(QPointF(x, baseline), text);
        x += QFontMetrics(font).horizontalAdvance(text);
    };
    draw(sentText(), f, th.text.onDark);
    x += kGapDot;
    draw(QString(u'·'), f, th.text.onDarkDim);
    x += kGapDot;
    draw(undoText(), bold, th.text.onDark);
    draw(QStringLiteral(" ") + hintText(), f, th.text.onDarkDim);
}
