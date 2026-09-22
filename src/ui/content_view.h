// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#pragma once

// What MainWindow's content stack is showing. Tracked explicitly because the
// current-conversation id is not a usable proxy for it: the id is empty both
// before any conversation has opened in a workspace AND while the user sits on
// an overview page (Threads / Saved messages) — two states that timer-driven
// code must tell apart.
enum class ContentView {
    None,         // nothing opened yet (start-up, after a workspace switch / logout)
    Conversation, // a chat's message list or its canvas tab
    Overview,     // a workspace-wide page the user navigated to on purpose
};

// Whether a freshly landed conversation-list snapshot should reopen the
// conversation the user last had open. This is a start-up affordance only: the
// snapshot producer also fires on every activity/presence/star sweep, so
// applying it while an overview is showing yanks the user back into the chat
// they just left (issue #81).
constexpr bool shouldRestoreLastConv(ContentView view) {
    return view == ContentView::None;
}
