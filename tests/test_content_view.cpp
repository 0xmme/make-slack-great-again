// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "ui/content_view.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("last conversation is restored only while nothing has been shown yet", "[content_view]") {
    CHECK(shouldRestoreLastConv(ContentView::None));
    CHECK_FALSE(shouldRestoreLastConv(ContentView::Conversation));
    CHECK_FALSE(shouldRestoreLastConv(ContentView::Overview));
}

// Issue #81: open a channel, switch to Threads / Saved messages, wait — the
// next conversation-list snapshot (activity poll, presence sweep, ...) used to
// treat the empty current-conversation id as "first populate" and reopen the
// channel. Replays the reporter's steps as content-view transitions.
TEST_CASE(
    "a snapshot landing on an overview page does not reopen the last chat", "[content_view]"
) {
    ContentView view = ContentView::None;
    CHECK(shouldRestoreLastConv(view)); // start-up: first snapshot restores

    view = ContentView::Conversation; // step 1: click a channel
    CHECK_FALSE(shouldRestoreLastConv(view));

    view = ContentView::Overview;             // step 2: click "Threads" / "Saved messages"
    CHECK_FALSE(shouldRestoreLastConv(view)); // step 3: wait — snapshots keep landing
    CHECK_FALSE(shouldRestoreLastConv(view));

    view = ContentView::None; // a workspace switch starts over: restore again
    CHECK(shouldRestoreLastConv(view));
}
