// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include "backend/domain.h"

#include <QFrame>
#include <vector>

class BrowseListView;
class ImageCache;
class QLabel;
class QStackedLayout;
class StyledLineEdit;

// Who is in the open channel or group DM: a searchable list under the header
// control that opened it. Auto-dismisses on outside click (Qt::Popup), like the
// GIF picker. The host looks the members up (Session::loadMembers, findUser);
// the popup only shows and filters them. Activating a row asks for a DM with
// that person.
class MembersPopup : public QFrame {
    Q_OBJECT
public:
    explicit MembersPopup(ImageCache *imgCache, QWidget *parent = nullptr);

    // Show below `anchorGlobal` with an empty search, in the loading state
    // until setMembers() or showError(). `expectedCount` sizes the panel: it
    // can't reliably grow once shown (Wayland), so the host passes what it
    // already knows (the channel's member count, a group DM's members).
    void open(const QRect &anchorGlobal, int expectedCount);

    // Replace the list; the search text stays. Sorted by name, `me` marked,
    // deactivated accounts left out.
    void setMembers(const std::vector<User> &members, const UserId &me);
    // Show `message` (the load failed) where the list goes.
    void showError(const QString &message);

    // Rows passing the search, for tests.
    int visibleCount() const;

signals:
    void memberActivated(UserId user);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void applyTheme();
    void applyFilter();
    // A message in place of the list (loading, failure, no match).
    void showMessage(const QString &message);

    static constexpr int kWidth   = 340;
    static constexpr int kMaxRows = 6; // the panel's height; longer lists scroll

    QLabel         *_title   = nullptr;
    StyledLineEdit *_search  = nullptr;
    QStackedLayout *_body    = nullptr; // list / message
    BrowseListView *_list    = nullptr;
    QLabel         *_message = nullptr;
    QString         _error; // set by showError(); wins over the list
    bool            _loading = true;
};
