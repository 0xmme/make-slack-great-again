// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "canvas_display.h"
#include "canvas_emoji.h"
#include "session/session.h"
#include "text/mrkdwn_parser.h"
#include "util/emoji.h"

#include <QFont>
#include <QRegularExpression>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocument>

namespace CanvasDisplay {

namespace {

// Same scheme as MsgRender::kUserAnchorPrefix; spelled out so this TU doesn't
// drag the message renderer into every target that links the canvas code.
constexpr QLatin1StringView kUserAnchor("msga://user/");

QString memberLabel(const QString &id, const Session *session) {
    const User *u = session ? session->findUser(UserId{id}) : nullptr;
    return u ? u->displayLabel() : id;
}

} // namespace

QString title(const QString &raw, const Session *session) {
    static const QRegularExpression kMention(QStringLiteral("<@([UW][A-Z0-9]+)(?:\\|([^>]*))?>"));
    QString                         decoded = Emoji::expandCodes(MrkdwnParser::decodeEntities(raw));
    QString                         out;
    qsizetype                       last = 0;
    for (auto it = kMention.globalMatch(decoded); it.hasNext();) {
        const auto m = it.next();
        out += QStringView(decoded).mid(last, m.capturedStart() - last);
        const User *u = session ? session->findUser(UserId{m.captured(1)}) : nullptr;
        out += QLatin1Char('@') + (u                          ? u->displayLabel()
                                   : !m.captured(2).isEmpty() ? m.captured(2)
                                                              : m.captured(1));
        last = m.capturedEnd();
    }
    out += QStringView(decoded).mid(last);
    return out.trimmed();
}

QString prepareHtml(const QString &rawHtml, const Session *session) {
    QString html = rawHtml;

    // Standard emoji: <img … data-is-slack …>:name:</img>. The img is void to
    // Qt, so the code after it would render as a second copy of the emoji.
    static const QRegularExpression kSlackEmojiImg(
        QStringLiteral("<img\\b[^>]*\\bdata-is-slack\\b[^>]*>"),
        QRegularExpression::CaseInsensitiveOption
    );
    static const QRegularExpression kImgClose(
        QStringLiteral("</img\\s*>"), QRegularExpression::CaseInsensitiveOption
    );
    html.remove(kSlackEmojiImg);
    html.remove(kImgClose);

    static const QHash<QString, QString> kNoCustom;
    html = CanvasEmoji::expandInHtml(html, session ? session->emojiMap() : kNoCustom);

    // Hyperlinks come as a non-standard <lnk href>…</lnk> tag the rich-text
    // engine doesn't recognize (it drops the href), so they would render as
    // dead plain text.
    static const QRegularExpression lnkOpen(
        QStringLiteral("<lnk\\b"), QRegularExpression::CaseInsensitiveOption
    );
    static const QRegularExpression lnkClose(
        QStringLiteral("</lnk\\s*>"), QRegularExpression::CaseInsensitiveOption
    );
    html.replace(lnkOpen, QStringLiteral("<a"));
    html.replace(lnkClose, QStringLiteral("</a>"));

    // Inline content images are pinned to a tiny placeholder size (e.g.
    // width='64' height='23'); the official client ignores that and scales them
    // to the column (toMarkdown emits ![alt](src) regardless of size).
    static const QRegularExpression imgRe(
        QStringLiteral("<img\\b[^>]*>"), QRegularExpression::CaseInsensitiveOption
    );
    static const QRegularExpression sizeAttr(
        QStringLiteral("\\s(?:width|height)=['\"][^'\"]*['\"]"),
        QRegularExpression::CaseInsensitiveOption
    );
    // Member mentions: a bare, href-less anchor holding "@<id>".
    static const QRegularExpression mentionRe(
        QStringLiteral("<a>@([UW][A-Z0-9]+)</a>"), QRegularExpression::CaseInsensitiveOption
    );
    static const QRegularExpression pieceRe(
        imgRe.pattern() + QLatin1Char('|') + mentionRe.pattern(),
        QRegularExpression::CaseInsensitiveOption
    );
    QString   out;
    qsizetype last = 0;
    for (auto it = pieceRe.globalMatch(html); it.hasNext();) {
        const auto m = it.next();
        out += QStringView(html).mid(last, m.capturedStart() - last);
        if (const QString id = m.captured(1); !id.isEmpty()) {
            out += QStringLiteral("<a href=\"%1%2\">@%3</a>")
                       .arg(kUserAnchor, id, memberLabel(id, session).toHtmlEscaped());
        } else {
            QString tag = m.captured(0);
            if (tag.contains(QLatin1String("collab-slack-blob")))
                tag.replace(sizeAttr, QString());
            out += tag;
        }
        last = m.capturedEnd();
    }
    out += QStringView(html).mid(last);
    return out;
}

int headingPx(int level, int bodyPx) {
    return bodyPx + (level == 1 ? 8 : level == 2 ? 5 : level == 3 ? 2 : 0);
}

void styleHeadings(QTextDocument *doc, int bodyPx) {
    if (!doc)
        return;
    QTextCursor c(doc);
    for (QTextBlock b = doc->begin(); b.isValid(); b = b.next()) {
        const int lvl = b.blockFormat().headingLevel();
        if (lvl <= 0)
            continue;
        const int px = headingPx(lvl, bodyPx);
        // Per fragment so inline runs keep their own colour/italic/bold. A plain
        // mergeCharFormat can't drop the FontSizeAdjustment that Qt's <h*> import
        // stamps on (it inflates the size); replacing each fragment's format with
        // a copy that has the adjustment cleared and the pixel size set does.
        for (auto it = b.begin(); !it.atEnd(); ++it) {
            const QTextFragment frag = it.fragment();
            if (!frag.isValid())
                continue;
            QTextCharFormat cf = frag.charFormat();
            QFont           f  = cf.font();
            f.setPixelSize(px);
            f.setBold(true);
            cf.setFont(f);
            cf.clearProperty(QTextFormat::FontSizeAdjustment);
            c.setPosition(frag.position());
            c.setPosition(frag.position() + frag.length(), QTextCursor::KeepAnchor);
            c.setCharFormat(cf);
        }
    }
}

} // namespace CanvasDisplay
