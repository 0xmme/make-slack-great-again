// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include "ui/app_dialog/app_dialog.h"

class QLabel;
class StyledButton;
class StyledLineEdit;

// "Name conversation" for a group DM: a local alias shown instead of the
// member list (Conversation::localName). Nothing goes to the server.
//
//   currentName — the alias already set (empty = none), prefilled and selected
//   derivedName — the title the list shows without an alias (the members);
//                 used as the placeholder so clearing the field previews it
//
// After exec() == Accepted: name() is the trimmed alias — empty means "clear
// it, list the members again".
class RenameConversationDialog : public AppDialog {
    Q_OBJECT
public:
    RenameConversationDialog(
        const QString &currentName, const QString &derivedName, QWidget *parent = nullptr
    );

    QString name() const;

protected:
    void applyTheme() override;

private:
    QLabel         *_sectionLabel = nullptr;
    StyledLineEdit *_edit         = nullptr;
    QLabel         *_hint         = nullptr;
    StyledButton   *_saveBtn      = nullptr;
    StyledButton   *_cancelBtn    = nullptr;
};
