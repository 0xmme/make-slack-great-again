// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "ui/transcript_dialog/transcript_dialog.h"
#include "ui/styled_button/styled_button.h"
#include "ui/theme.h"
#include "util/clipboard.h"

#include <QLabel>
#include <QScrollArea>
#include <QTimer>
#include <QVBoxLayout>

namespace {
constexpr int kBodyMaxH = 360;
}

TranscriptDialog::TranscriptDialog(const QString &subtitle, QWidget *parent)
    : AppDialog(tr("Transcript (auto-generated)"), parent, Scroll::Disabled) {
    auto *cl = contentLayout();

    _subtitle = new QLabel(subtitle);
    cl->addWidget(_subtitle);
    cl->addSpacing(Th::c().spacing.md);

    _body = new QLabel(tr("Loading…"));
    _body->setTextFormat(Qt::RichText);
    _body->setWordWrap(true);
    _body->setTextInteractionFlags(Qt::TextSelectableByMouse);
    _body->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    _body->setAutoFillBackground(false);

    _scroll = new QScrollArea;
    _scroll->setWidgetResizable(true);
    _scroll->setFrameShape(QFrame::NoFrame);
    _scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _scroll->viewport()->setAutoFillBackground(false);
    _scroll->setWidget(_body);
    _body->setAutoFillBackground(false); // setWidget() force-enables it
    _scroll->setMaximumHeight(kBodyMaxH);
    cl->addWidget(_scroll, 1);

    _copyBtn = new StyledButton(tr("Copy"), StyledButton::Variant::Primary);
    _copyBtn->setEnabled(false);
    connect(_copyBtn, &QPushButton::clicked, this, [this] {
        Clipboard::setText(_plain);
        _copyBtn->setText(tr("Copied"));
        QTimer::singleShot(1400, _copyBtn, [this] { _copyBtn->setText(tr("Copy")); });
    });
    addButtonRow(nullptr, nullptr, _copyBtn);

    applyTheme();
    updateCard();
}

void TranscriptDialog::setCues(const std::vector<MsgRender::VttCue> &cues) {
    QString       html;
    QStringList   plain;
    const QString stamp = Th::qss(Th::c().text.secondary);
    for (const auto &c : cues) {
        const QString t = MsgRender::formatDuration(c.startMs);
        html += QStringLiteral(
                    "<p style=\"margin:0 0 6px 0\"><span style=\"color:%1\">%2</span>"
                    "&nbsp;&nbsp;%3</p>"
        )
                    .arg(stamp, t.toHtmlEscaped(), c.text.toHtmlEscaped());
        plain << t + QStringLiteral("  ") + c.text;
    }
    _plain = plain.join('\n');
    _body->setText(html);
    _copyBtn->setEnabled(!cues.empty());
    updateCard();
}

void TranscriptDialog::setText(const QString &text) {
    setCues({MsgRender::VttCue{0, text}});
}

void TranscriptDialog::setFailed(const QString &error) {
    _body->setText(error.toHtmlEscaped());
    _copyBtn->setEnabled(false);
    updateCard();
}

void TranscriptDialog::applyTheme() {
    AppDialog::applyTheme();
    _subtitle->setStyleSheet(QStringLiteral("color: %1;").arg(Th::qss(Th::c().text.secondary)));
    _body->setStyleSheet(QStringLiteral("color: %1;").arg(Th::qss(Th::c().text.primary)));
    _scroll->setStyleSheet(
        QStringLiteral("QScrollArea { background: transparent; }") + Th::scrollBarQss()
    );
}
