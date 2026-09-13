// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

#include "backend/domain.h"
#include "ui/app_dialog/app_dialog.h"
#include "ui/conv_list/named_conversation.h"

#include <algorithm>
#include <optional>
#include <vector>

class BrowseListView;
class ImageCache;
class QLabel;
class StyledLineEdit;
class WorkspaceTabStrip;

// Ctrl/Cmd+K quick switcher: type a few letters, hit Enter, land in the
// conversation (issue #52). Lists the conversations the user is already in —
// channels, DMs and group DMs — most recently active first, so an empty query
// is a "recent chats" list. Matching is fuzzy (issue #60): the typed letters
// need only appear in order, so "xdg" finds #xd-general and "bb" finds Bob
// Builder; matches are ranked best-first, with group DMs ranked under a 1:1 DM
// or channel that matches as well (issue #61).
//
// With several workspaces signed in, a strip of workspace bubbles sits above
// the list, one tab per workspace, opening on the active one. ←/→ (or Tab)
// move between them and a bubble click does too. Typing re-aims the tab at
// the workspace holding the best match, so "gen" lands on the workspace that
// has #general even if it isn't the one on screen; a tab the user picked by
// hand while a query was up stays put while the query grows (unless it runs
// out of matches — a tab picked before typing doesn't pin), and
// workspaces with nothing for the query are dimmed so the eye can skip them.
// Activation reports the workspace alongside the conversation.
//
// Deliberately not a second channel browser: BrowseChannelsDialog is for finding
// something you are *not* in (it can join, it has a People tab, it hits the
// network). This one is pure navigation over what the sidebars already hold.
class QuickSwitcherDialog : public AppDialog {
    Q_OBJECT
public:
    struct Workspace {
        QString                        teamId;
        QString                        name;
        QString                        iconUrl;
        std::vector<NamedConversation> conversations; // most recent first
    };

    // `activeTeamId` selects the initial tab (falls back to the first).
    QuickSwitcherDialog(
        std::vector<Workspace> workspaces,
        const QString         &activeTeamId,
        ImageCache            *imgCache,
        QWidget               *parent = nullptr
    );
    // Single workspace, no tab strip; activation reports an empty team id.
    QuickSwitcherDialog(
        std::vector<NamedConversation> conversations,
        ImageCache                    *imgCache,
        QWidget                       *parent = nullptr
    );

signals:
    void conversationActivated(const QString &teamId, ConversationId id);

protected:
    void applyTheme() override;
    void showEvent(QShowEvent *e) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    int  cardWidth(int availOverlayWidth) const override {
        return std::min(availOverlayWidth, kCardW);
    }
    int minCardHeight() const override { return kCardMinH; }

private:
    void                  buildItems(int workspaceIndex);
    // Query changed: re-aim the tab if warranted, then refreshList().
    void                  applyFilter(const QString &query);
    // Filter the shown workspace's rows, preselect the top one, swap in the
    // empty notice when nothing passes.
    void                  refreshList(const QString &query);
    void                  onTabChanged(int index);
    void                  stepWorkspace(int delta);
    // Best fuzzy score over one workspace's conversations, ranking bias
    // included, or nullopt when nothing there matches.
    std::optional<double> bestScore(const Workspace &ws, const QString &query) const;

    StyledLineEdit    *_searchEdit = nullptr;
    WorkspaceTabStrip *_tabs       = nullptr;
    BrowseListView    *_list       = nullptr;
    QLabel            *_hint       = nullptr;
    QLabel            *_empty      = nullptr;

    std::vector<Workspace> _workspaces;
    ImageCache            *_imgCache       = nullptr;
    int                    _shownWorkspace = -1;    // whose items the list holds
    bool                   _autoSwitching  = false; // tab change driven by the query
    bool                   _manualTab      = false; // user picked the tab since typing began

    static constexpr int kCardW    = 560;
    static constexpr int kCardMinH = 420;
    static constexpr int kListMinH = 300;
};
