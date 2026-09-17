<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="en_US" sourcelanguage="en_US">
<context>
    <name>slack::OAuthFlow</name>
    <message>
        <location filename="../src/backend/slack/oauth_flow.cpp" line="45"/>
        <source>No Slack app keys are set up yet.

Open Settings → System, choose “Slack app keys”, and paste your client ID, client secret and app token. Building msga yourself? Put them in credentials.cmake instead and rebuild.</source>
        <translation>No Slack app keys are set up yet.

Open Settings → System, choose “Slack app keys”, and paste your client ID, client secret and app token. Building msga yourself? Put them in credentials.cmake instead and rebuild.</translation>
    </message>
</context>
<context>
    <name>BrowserLogin</name>
    <message>
        <location filename="../src/backend/slack/session_import/browser_login.cpp" line="423"/>
        <source>Opening %1…</source>
        <translation>Opening %1…</translation>
    </message>
    <message>
        <location filename="../src/backend/slack/session_import/browser_login.cpp" line="460"/>
        <source>Sign in to Slack in the browser window — msga picks it up automatically.</source>
        <translation>Sign in to Slack in the browser window — msga picks it up automatically.</translation>
    </message>
    <message>
        <location filename="../src/backend/slack/session_import/browser_login.cpp" line="632"/>
        <source>Signed in — finishing up in msga. You can close this.</source>
        <translation>Signed in — finishing up in msga. You can close this.</translation>
    </message>
    <message>
        <location filename="../src/backend/slack/session_import/browser_login.cpp" line="673"/>
        <source>Signed in — looking up your workspaces…</source>
        <translation>Signed in — looking up your workspaces…</translation>
    </message>
</context>
<context>
    <name>teams::OAuthFlow</name>
    <message>
        <location filename="../src/backend/teams/oauth_flow.cpp" line="53"/>
        <source>Microsoft Teams app credentials are not configured.

Set MSGA_TEAMS_CLIENT_ID in credentials.cmake and rebuild.</source>
        <translation>Microsoft Teams app credentials are not configured.

Set MSGA_TEAMS_CLIENT_ID in credentials.cmake and rebuild.</translation>
    </message>
</context>
<context>
    <name>LlmProvider</name>
    <message>
        <location filename="../src/llm/llm_provider.cpp" line="160"/>
        <source>API key</source>
        <translation>API key</translation>
    </message>
    <message>
        <location filename="../src/llm/llm_provider.cpp" line="204"/>
        <source>%1 is not connected</source>
        <translation>%1 is not connected</translation>
    </message>
    <message>
        <location filename="../src/llm/llm_provider.cpp" line="239"/>
        <source>%1 does not support speech-to-text</source>
        <translation>%1 does not support speech-to-text</translation>
    </message>
    <message>
        <location filename="../src/llm/llm_provider.cpp" line="244"/>
        <source>%1 is not connected</source>
        <translation>%1 is not connected</translation>
    </message>
</context>
<context>
    <name>LlmService</name>
    <message>
        <location filename="../src/llm/llm_service.cpp" line="184"/>
        <source>No AI provider connected — connect one in Settings → AI assistance</source>
        <translation>No AI provider connected — connect one in Settings → AI assistance</translation>
    </message>
    <message>
        <location filename="../src/llm/llm_service.cpp" line="196"/>
        <source>No AI provider connected — connect one in Settings → AI assistance</source>
        <translation>No AI provider connected — connect one in Settings → AI assistance</translation>
    </message>
</context>
<context>
    <name>LlmWire</name>
    <message>
        <location filename="../src/llm/llm_wire.cpp" line="71"/>
        <source>unknown error</source>
        <translation>unknown error</translation>
    </message>
    <message>
        <location filename="../src/llm/llm_wire.cpp" line="89"/>
        <source>network error</source>
        <translation>network error</translation>
    </message>
    <message>
        <location filename="../src/llm/llm_wire.cpp" line="94"/>
        <source>This server has no speech-to-text endpoint (HTTP 404)</source>
        <translation>This server has no speech-to-text endpoint (HTTP 404)</translation>
    </message>
    <message>
        <location filename="../src/llm/llm_wire.cpp" line="96"/>
        <source>No chat endpoint at this URL (HTTP 404) — most servers expect it to end in /v1</source>
        <translation>No chat endpoint at this URL (HTTP 404) — most servers expect it to end in /v1</translation>
    </message>
    <message>
        <location filename="../src/llm/llm_wire.cpp" line="98"/>
        <source>HTTP %1</source>
        <translation>HTTP %1</translation>
    </message>
    <message>
        <location filename="../src/llm/llm_wire.cpp" line="99"/>
        <source>HTTP %1: %2</source>
        <translation>HTTP %1: %2</translation>
    </message>
    <message>
        <location filename="../src/llm/llm_wire.cpp" line="119"/>
        <source>Unexpected response from server (not JSON)</source>
        <translation>Unexpected response from server (not JSON)</translation>
    </message>
    <message>
        <location filename="../src/llm/llm_wire.cpp" line="239"/>
        <source>Unexpected response from server (no text)</source>
        <translation>Unexpected response from server (no text)</translation>
    </message>
    <message>
        <location filename="../src/llm/llm_wire.cpp" line="291"/>
        <source>Unexpected response from server (no choices)</source>
        <translation>Unexpected response from server (no choices)</translation>
    </message>
</context>
<context>
    <name>OAuthLoopbackFlow</name>
    <message>
        <location filename="../src/llm/oauth_loopback.cpp" line="45"/>
        <source>Could not listen on port %1: %2</source>
        <translation>Could not listen on port %1: %2</translation>
    </message>
    <message>
        <location filename="../src/llm/oauth_loopback.cpp" line="92"/>
        <source>You can close this window and return to msga.</source>
        <translation>You can close this window and return to msga.</translation>
    </message>
</context>
<context>
    <name>Media::AudioPlayer</name>
    <message>
        <location filename="../src/media/audio_engine_linux.cpp" line="73"/>
        <source>This audio format can't be played here</source>
        <translation>This audio format can't be played here</translation>
    </message>
    <message>
        <location filename="../src/media/audio_engine_linux.cpp" line="82"/>
        <source>This audio format can't be played here</source>
        <translation>This audio format can't be played here</translation>
    </message>
    <message>
        <location filename="../src/media/audio_engine_linux.cpp" line="133"/>
        <source>This audio format needs ffmpeg installed to play</source>
        <translation>This audio format needs ffmpeg installed to play</translation>
    </message>
    <message>
        <location filename="../src/media/audio_engine_linux.cpp" line="209"/>
        <source>This audio format can't be played here</source>
        <translation>This audio format can't be played here</translation>
    </message>
    <message>
        <location filename="../src/media/audio_engine_linux.cpp" line="221"/>
        <source>This audio format needs ffmpeg installed to play</source>
        <translation>This audio format needs ffmpeg installed to play</translation>
    </message>
    <message>
        <location filename="../src/media/audio_engine_linux.cpp" line="333"/>
        <source>This audio format needs ffmpeg installed to play</source>
        <translation>This audio format needs ffmpeg installed to play</translation>
    </message>
    <message>
        <location filename="../src/media/audio_engine_linux.cpp" line="423"/>
        <source>No audio output found (needs pw-cat, paplay or aplay)</source>
        <translation>No audio output found (needs pw-cat, paplay or aplay)</translation>
    </message>
    <message>
        <location filename="../src/media/audio_engine_linux.cpp" line="489"/>
        <source>Audio output failed</source>
        <translation>Audio output failed</translation>
    </message>
    <message>
        <location filename="../src/media/audio_engine_win.cpp" line="43"/>
        <source>Audio playback is unavailable</source>
        <translation>Audio playback is unavailable</translation>
    </message>
    <message>
        <location filename="../src/media/audio_engine_win.cpp" line="51"/>
        <source>This audio format can't be played here</source>
        <translation>This audio format can't be played here</translation>
    </message>
    <message>
        <location filename="../src/media/audio_engine_win.cpp" line="120"/>
        <source>This audio format can't be played here</source>
        <translation>This audio format can't be played here</translation>
    </message>
    <message>
        <location filename="../src/media/audio_engine_win.cpp" line="138"/>
        <source>This audio format can't be played here</source>
        <translation>This audio format can't be played here</translation>
    </message>
    <message>
        <location filename="../src/media/audio_engine_win.cpp" line="150"/>
        <source>Audio playback failed</source>
        <translation>Audio playback failed</translation>
    </message>
</context>
<context>
    <name>GifSearch</name>
    <message>
        <location filename="../src/network/gif_search.cpp" line="62"/>
        <source>GIPHY rate limit reached. Try again shortly.</source>
        <translation>GIPHY rate limit reached. Try again shortly.</translation>
    </message>
    <message>
        <location filename="../src/network/gif_search.cpp" line="64"/>
        <source>GIPHY request failed (HTTP %1).</source>
        <translation>GIPHY request failed (HTTP %1).</translation>
    </message>
    <message>
        <location filename="../src/network/gif_search.cpp" line="65"/>
        <source>Could not reach GIPHY — check your connection.</source>
        <translation>Could not reach GIPHY — check your connection.</translation>
    </message>
    <message>
        <location filename="../src/network/gif_search.cpp" line="114"/>
        <source>No GIPHY API key configured.</source>
        <translation>No GIPHY API key configured.</translation>
    </message>
    <message>
        <location filename="../src/network/gif_search.cpp" line="144"/>
        <source>GIPHY rejected this API key.</source>
        <translation>GIPHY rejected this API key.</translation>
    </message>
</context>
<context>
    <name>Session</name>
    <message>
        <location filename="../src/session/session.cpp" line="56"/>
        <source> — sign in to this workspace again to grant the new permission</source>
        <translation> — sign in to this workspace again to grant the new permission</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="66"/>
        <source>You can't reply to this message.</source>
        <translation>You can't reply to this message.</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="68"/>
        <source>You're not a member of this channel.</source>
        <translation>You're not a member of this channel.</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="70"/>
        <source>This conversation is archived.</source>
        <translation>This conversation is archived.</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="72"/>
        <source>The message is too long.</source>
        <translation>The message is too long.</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="74"/>
        <source>This conversation no longer exists.</source>
        <translation>This conversation no longer exists.</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="76"/>
        <source>You don't have permission to post here.</source>
        <translation>You don't have permission to post here.</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="416"/>
        <source>Couldn't send message: %1</source>
        <translation>Couldn't send message: %1</translation>
    </message>
    <message numerus="yes">
        <location filename="../src/session/session.cpp" line="512"/>
        <source>Slack is rate-limiting requests (%1) — retrying in %n second(s).</source>
        <translation>
            <numerusform>Slack is rate-limiting requests (%1) — retrying in %n second.</numerusform>
            <numerusform>Slack is rate-limiting requests (%1) — retrying in %n seconds.</numerusform>
        </translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="1804"/>
        <source>Unknown user</source>
        <translation>Unknown user</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="1942"/>
        <source>Moved from the channel · originally posted by %1 on %2 at %3</source>
        <translation>Moved from the channel · originally posted by %1 on %2 at %3</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="1977"/>
        <source>Couldn't move the message — the original is still in place.</source>
        <translation>Couldn't move the message — the original is still in place.</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2056"/>
        <source>No such user: %1</source>
        <translation>No such user: %1</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2107"/>
        <source>Usage: /dnd [duration, e.g. 30m or 2h] — or /dnd off to resume</source>
        <translation>Usage: /dnd [duration, e.g. 30m or 2h] — or /dnd off to resume</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2123"/>
        <source>Command /%1 failed: %2</source>
        <translation>Command /%1 failed: %2</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2158"/>
        <source>Could not change presence: %1</source>
        <translation>Could not change presence: %1</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2192"/>
        <source>Could not set status: %1</source>
        <translation>Could not set status: %1</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2213"/>
        <source>Could not update notifications: %1</source>
        <translation>Could not update notifications: %1</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2239"/>
        <source>Could not update profile: %1</source>
        <translation>Could not update profile: %1</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2260"/>
        <source>Could not update avatar: %1</source>
        <translation>Could not update avatar: %1</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2340"/>
        <source>Upload failed: %1</source>
        <translation>Upload failed: %1</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2383"/>
        <source>Could not load canvas: %1</source>
        <translation>Could not load canvas: %1</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2414"/>
        <source>Could not create canvas: %1</source>
        <translation>Could not create canvas: %1</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2430"/>
        <source>Canvas edit failed: %1</source>
        <translation>Canvas edit failed: %1</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="2448"/>
        <source>Canvas deletion failed: %1</source>
        <translation>Canvas deletion failed: %1</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="3019"/>
        <source>Couldn't set the reminder: %1</source>
        <translation>Couldn't set the reminder: %1</translation>
    </message>
    <message>
        <location filename="../src/session/session.cpp" line="3048"/>
        <source>Couldn't remove the reminder: %1</source>
        <translation>Couldn't remove the reminder: %1</translation>
    </message>
</context>
<context>
    <name>MrkdwnParser</name>
    <message>
        <location filename="../src/text/mrkdwn_parser.cpp" line="92"/>
        <source>Today</source>
        <translation>Today</translation>
    </message>
    <message>
        <location filename="../src/text/mrkdwn_parser.cpp" line="94"/>
        <source>Yesterday</source>
        <translation>Yesterday</translation>
    </message>
    <message>
        <location filename="../src/text/mrkdwn_parser.cpp" line="96"/>
        <source>Tomorrow</source>
        <translation>Tomorrow</translation>
    </message>
</context>
<context>
    <name>BrowseChannelsDialog</name>
    <message>
        <location filename="../src/ui/browse_channels_dialog/browse_channels_dialog.cpp" line="49"/>
        <source>Search for channels</source>
        <translation>Search for channels</translation>
    </message>
    <message>
        <location filename="../src/ui/browse_channels_dialog/browse_channels_dialog.cpp" line="55"/>
        <source>Create Channel</source>
        <translation>Create Channel</translation>
    </message>
    <message>
        <location filename="../src/ui/browse_channels_dialog/browse_channels_dialog.cpp" line="72"/>
        <source>Channels</source>
        <translation>Channels</translation>
    </message>
    <message>
        <location filename="../src/ui/browse_channels_dialog/browse_channels_dialog.cpp" line="79"/>
        <source>People</source>
        <translation>People</translation>
    </message>
    <message>
        <location filename="../src/ui/browse_channels_dialog/browse_channels_dialog.cpp" line="154"/>
        <source>%1 %2</source>
        <translation>%1 %2</translation>
    </message>
    <message>
        <location filename="../src/ui/browse_channels_dialog/browse_channels_dialog.cpp" line="156"/>
        <source>member</source>
        <translation>member</translation>
    </message>
    <message>
        <location filename="../src/ui/browse_channels_dialog/browse_channels_dialog.cpp" line="156"/>
        <source>members</source>
        <translation>members</translation>
    </message>
    <message>
        <location filename="../src/ui/browse_channels_dialog/browse_channels_dialog.cpp" line="219"/>
        <source>Search for channels</source>
        <translation>Search for channels</translation>
    </message>
    <message>
        <location filename="../src/ui/browse_channels_dialog/browse_channels_dialog.cpp" line="219"/>
        <source>Search for people</source>
        <translation>Search for people</translation>
    </message>
</context>
<context>
    <name>BrowseListView</name>
    <message>
        <location filename="../src/ui/browse_channels_dialog/browse_list_view.cpp" line="272"/>
        <source>Joined</source>
        <translation>Joined</translation>
    </message>
</context>
<context>
    <name>CanvasPage</name>
    <message>
        <location filename="../src/ui/canvas_page/canvas_page.cpp" line="268"/>
        <source>Your canvas title</source>
        <translation>Your canvas title</translation>
    </message>
    <message>
        <location filename="../src/ui/canvas_page/canvas_page.cpp" line="272"/>
        <source>Go ahead, start writing!</source>
        <translation>Go ahead, start writing!</translation>
    </message>
    <message>
        <location filename="../src/ui/canvas_page/canvas_page.cpp" line="657"/>
        <source>This canvas was created with Slack's built-in editor and is not editable through the Slack API — it is read-only here.</source>
        <translation>This canvas was created with Slack's built-in editor and is not editable through the Slack API — it is read-only here.</translation>
    </message>
    <message>
        <location filename="../src/ui/canvas_page/canvas_page.cpp" line="659"/>
        <source>You don't have access to this canvas.</source>
        <translation>You don't have access to this canvas.</translation>
    </message>
    <message>
        <location filename="../src/ui/canvas_page/canvas_page.cpp" line="676"/>
        <source>Copy link</source>
        <translation>Copy link</translation>
    </message>
    <message>
        <location filename="../src/ui/canvas_page/canvas_page.cpp" line="685"/>
        <source>Delete canvas</source>
        <translation>Delete canvas</translation>
    </message>
    <message>
        <location filename="../src/ui/canvas_page/canvas_page.cpp" line="207"/>
        <source>Delete canvas</source>
        <translation>Delete canvas</translation>
    </message>
    <message>
        <location filename="../src/ui/canvas_page/canvas_page.cpp" line="211"/>
        <source>The canvas will be deleted for everyone in the conversation.
This action cannot be undone.</source>
        <translation>The canvas will be deleted for everyone in the conversation.
This action cannot be undone.</translation>
    </message>
    <message>
        <location filename="../src/ui/canvas_page/canvas_page.cpp" line="226"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="../src/ui/canvas_page/canvas_page.cpp" line="229"/>
        <source>Delete canvas</source>
        <translation>Delete canvas</translation>
    </message>
</context>
<context>
    <name>AttachmentStrip</name>
    <message>
        <location filename="../src/ui/composer/attachment_strip.cpp" line="297"/>
        <source>Remove attachment</source>
        <translation>Remove attachment</translation>
    </message>
</context>
<context>
    <name>ComposerWidget</name>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="107"/>
        <source>GIF</source>
        <translation>GIF</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="107"/>
        <source>GIF · %1</source>
        <translation>GIF · %1</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="436"/>
        <source>Subject</source>
        <translation>Subject</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="501"/>
        <source>Message #channel</source>
        <translation>Message #channel</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="543"/>
        <source>Attach file</source>
        <translation>Attach file</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="558"/>
        <source>Emoji</source>
        <translation>Emoji</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="559"/>
        <source>Search GIFs</source>
        <translation>Search GIFs</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="561"/>
        <source>Mention</source>
        <translation>Mention</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="574"/>
        <source>Send message</source>
        <translation>Send message</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="584"/>
        <source>Schedule send</source>
        <translation>Schedule send</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="1547"/>
        <source>Send message</source>
        <translation>Send message</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="1551"/>
        <source>Search GIFs — needs a GIPHY API key</source>
        <translation>Search GIFs — needs a GIPHY API key</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="1639"/>
        <source>Send at</source>
        <translation>Send at</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="1639"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="1639"/>
        <source>Schedule</source>
        <translation>Schedule</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="1859"/>
        <source>Attach File</source>
        <translation>Attach File</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="1894"/>
        <source>URL</source>
        <translation>URL</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="1894"/>
        <source>Display text</source>
        <translation>Display text</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="1894"/>
        <source>Insert</source>
        <translation>Insert</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/composer_widget.cpp" line="1894"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
</context>
<context>
    <name>EditModeBanner</name>
    <message>
        <location filename="../src/ui/composer/edit_mode_banner.cpp" line="21"/>
        <source>Editing message</source>
        <translation>Editing message</translation>
    </message>
</context>
<context>
    <name>FormattingToolbar</name>
    <message>
        <location filename="../src/ui/composer/formatting_toolbar.cpp" line="59"/>
        <source>Bold</source>
        <translation>Bold</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/formatting_toolbar.cpp" line="60"/>
        <source>Italic</source>
        <translation>Italic</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/formatting_toolbar.cpp" line="62"/>
        <source>Underline</source>
        <translation>Underline</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/formatting_toolbar.cpp" line="64"/>
        <source>Strikethrough</source>
        <translation>Strikethrough</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/formatting_toolbar.cpp" line="65"/>
        <source>Link</source>
        <translation>Link</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/formatting_toolbar.cpp" line="67"/>
        <source>Ordered list</source>
        <translation>Ordered list</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/formatting_toolbar.cpp" line="68"/>
        <source>Bullet list</source>
        <translation>Bullet list</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/formatting_toolbar.cpp" line="69"/>
        <source>Blockquote</source>
        <translation>Blockquote</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/formatting_toolbar.cpp" line="70"/>
        <source>Inline code</source>
        <translation>Inline code</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/formatting_toolbar.cpp" line="71"/>
        <source>Code block</source>
        <translation>Code block</translation>
    </message>
</context>
<context>
    <name>MentionCompleter</name>
    <message>
        <location filename="../src/ui/composer/mention_completer.cpp" line="112"/>
        <source>Enter</source>
        <translation>Enter</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/mention_completer.cpp" line="161"/>
        <source>App</source>
        <translation>App</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/mention_completer.cpp" line="306"/>
        <source>Enter</source>
        <translation>Enter</translation>
    </message>
</context>
<context>
    <name>UndoSendPill</name>
    <message>
        <location filename="../src/ui/composer/undo_send_pill.cpp" line="22"/>
        <source>Message sent</source>
        <translation>Message sent</translation>
    </message>
    <message>
        <location filename="../src/ui/composer/undo_send_pill.cpp" line="26"/>
        <source>Undo</source>
        <translation>Undo</translation>
    </message>
</context>
<context>
    <name>ConvFooterWidget</name>
    <message numerus="yes">
        <location filename="../src/ui/conv_footer/conv_footer_widget.cpp" line="138"/>
        <source>%n background task(s) running</source>
        <translation>
            <numerusform>%n background task running</numerusform>
            <numerusform>%n background tasks running</numerusform>
        </translation>
    </message>
    <message>
        <location filename="../src/ui/conv_footer/conv_footer_widget.cpp" line="243"/>
        <source>Hidden — you appear away to everyone. Click to use automatic presence.</source>
        <translation>Hidden — you appear away to everyone. Click to use automatic presence.</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_footer/conv_footer_widget.cpp" line="249"/>
        <source>Away — you haven't used MSGA for a while. Any click or keystroke makes you active again (Settings → System → Presence).</source>
        <translation>Away — you haven't used MSGA for a while. Any click or keystroke makes you active again (Settings → System → Presence).</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_footer/conv_footer_widget.cpp" line="255"/>
        <source>Visible — connecting so you appear active without the official Slack app…</source>
        <translation>Visible — connecting so you appear active without the official Slack app…</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_footer/conv_footer_widget.cpp" line="260"/>
        <source>Visible — but you appear away while no official Slack app is connected. MSGA can't hold your presence on this workspace.</source>
        <translation>Visible — but you appear away while no official Slack app is connected. MSGA can't hold your presence on this workspace.</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_footer/conv_footer_widget.cpp" line="267"/>
        <source>Visible — but you appear away while no official Slack app is connected. MSGA can keep you active: Settings → System → Presence.</source>
        <translation>Visible — but you appear away while no official Slack app is connected. MSGA can keep you active: Settings → System → Presence.</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_footer/conv_footer_widget.cpp" line="273"/>
        <source>Visible — MSGA keeps you active. Click to appear hidden.</source>
        <translation>Visible — MSGA keeps you active. Click to appear hidden.</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_footer/conv_footer_widget.cpp" line="274"/>
        <source>Visible — using automatic presence. Click to appear hidden.</source>
        <translation>Visible — using automatic presence. Click to appear hidden.</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_footer/conv_footer_widget.cpp" line="347"/>
        <source>Profile &amp; status</source>
        <translation>Profile &amp; status</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_footer/conv_footer_widget.cpp" line="391"/>
        <source>Manage profile</source>
        <translation>Manage profile</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_footer/conv_footer_widget.cpp" line="397"/>
        <source>Manage status</source>
        <translation>Manage status</translation>
    </message>
</context>
<context>
    <name>ConvListWidget</name>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="853"/>
        <source>Open a direct message</source>
        <translation>Open a direct message</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="882"/>
        <source>Notify you about…</source>
        <translation>Notify you about…</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="884"/>
        <source>All new posts</source>
        <translation>All new posts</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="891"/>
        <source>Just mentions</source>
        <translation>Just mentions</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="898"/>
        <source>Mute and hide</source>
        <translation>Mute and hide</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="912"/>
        <source>Unstar channel</source>
        <translation>Unstar channel</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="912"/>
        <source>Star channel</source>
        <translation>Star channel</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="919"/>
        <source>Leave channel</source>
        <translation>Leave channel</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="935"/>
        <source>Name conversation…</source>
        <translation>Name conversation…</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="935"/>
        <source>Rename conversation…</source>
        <translation>Rename conversation…</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="940"/>
        <source>Unstar conversation</source>
        <translation>Unstar conversation</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="940"/>
        <source>Star conversation</source>
        <translation>Star conversation</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="947"/>
        <source>Leave conversation</source>
        <translation>Leave conversation</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="958"/>
        <source>Unmute</source>
        <translation>Unmute</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="958"/>
        <source>Mute</source>
        <translation>Mute</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1033"/>
        <source>Find a channel</source>
        <translation>Find a channel</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1034"/>
        <source>Create a channel</source>
        <translation>Create a channel</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1188"/>
        <source>Channels</source>
        <translation>Channels</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1189"/>
        <source>Direct messages</source>
        <translation>Direct messages</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1190"/>
        <source>Starred</source>
        <translation>Starred</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1191"/>
        <source>Agents &amp; apps</source>
        <translation>Agents &amp; apps</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1260"/>
        <source>Threads</source>
        <translation>Threads</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1269"/>
        <source>Saved messages</source>
        <translation>Saved messages</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1289"/>
        <source>Add channels</source>
        <translation>Add channels</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1309"/>
        <source>%1 more %2</source>
        <translation>%1 more %2</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1309"/>
        <source>channel</source>
        <translation>channel</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1309"/>
        <source>channels</source>
        <translation>channels</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1501"/>
        <source>EXT</source>
        <translation>EXT</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1523"/>
        <source>you</source>
        <translation>you</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_list/conv_list_widget.cpp" line="1565"/>
        <source>you</source>
        <translation>you</translation>
    </message>
</context>
<context>
    <name>ConvSelectorWidget</name>
    <message>
        <location filename="../src/ui/conv_selector/conv_selector_widget.cpp" line="44"/>
        <source>Search channels and people…</source>
        <translation>Search channels and people…</translation>
    </message>
</context>
<context>
    <name>ConvTabsWidget</name>
    <message>
        <location filename="../src/ui/conv_tabs/conv_tabs_widget.cpp" line="62"/>
        <source>Messages</source>
        <translation>Messages</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_tabs/conv_tabs_widget.cpp" line="67"/>
        <source>Untitled</source>
        <translation>Untitled</translation>
    </message>
    <message>
        <location filename="../src/ui/conv_tabs/conv_tabs_widget.cpp" line="67"/>
        <source>Add canvas</source>
        <translation>Add canvas</translation>
    </message>
</context>
<context>
    <name>CreateChannelDialog</name>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="19"/>
        <source>Create a channel</source>
        <translation>Create a channel</translation>
    </message>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="33"/>
        <source>Name</source>
        <translation>Name</translation>
    </message>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="42"/>
        <source>e.g. plan-budget</source>
        <translation>e.g. plan-budget</translation>
    </message>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="46"/>
        <source>Channels are where conversations happen around a topic. Use a name that is easy to find and understand.</source>
        <translation>Channels are where conversations happen around a topic. Use a name that is easy to find and understand.</translation>
    </message>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="57"/>
        <source>Next</source>
        <translation>Next</translation>
    </message>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="77"/>
        <source>Visibility</source>
        <translation>Visibility</translation>
    </message>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="87"/>
        <source>Private — only specific people</source>
        <translation>Private — only specific people</translation>
    </message>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="90"/>
        <source>Can only be viewed or joined by invitation</source>
        <translation>Can only be viewed or joined by invitation</translation>
    </message>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="97"/>
        <source>Step 2 of 2</source>
        <translation>Step 2 of 2</translation>
    </message>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="98"/>
        <source>Back</source>
        <translation>Back</translation>
    </message>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="99"/>
        <source>Create</source>
        <translation>Create</translation>
    </message>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="139"/>
        <source>this workspace</source>
        <translation>this workspace</translation>
    </message>
    <message>
        <location filename="../src/ui/create_channel_dialog/create_channel_dialog.cpp" line="140"/>
        <source>Public — anyone in %1</source>
        <translation>Public — anyone in %1</translation>
    </message>
</context>
<context>
    <name>DeleteMessageDialog</name>
    <message>
        <location filename="../src/ui/delete_message_dialog/delete_message_dialog.cpp" line="17"/>
        <source>Delete message</source>
        <translation>Delete message</translation>
    </message>
    <message>
        <location filename="../src/ui/delete_message_dialog/delete_message_dialog.cpp" line="21"/>
        <source>This action cannot be undone.</source>
        <translation>This action cannot be undone.</translation>
    </message>
    <message>
        <location filename="../src/ui/delete_message_dialog/delete_message_dialog.cpp" line="75"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="../src/ui/delete_message_dialog/delete_message_dialog.cpp" line="76"/>
        <source>Delete</source>
        <translation>Delete</translation>
    </message>
</context>
<context>
    <name>EmojiGrid</name>
    <message>
        <location filename="../src/ui/emoji_picker/emoji_picker_popup.cpp" line="430"/>
        <source>Search all emoji</source>
        <translation>Search all emoji</translation>
    </message>
    <message>
        <location filename="../src/ui/emoji_picker/emoji_picker_popup.cpp" line="451"/>
        <source>Skin Tone</source>
        <translation>Skin Tone</translation>
    </message>
    <message>
        <location filename="../src/ui/emoji_picker/emoji_picker_popup.cpp" line="593"/>
        <source>Search Results</source>
        <translation>Search Results</translation>
    </message>
    <message>
        <location filename="../src/ui/emoji_picker/emoji_picker_popup.cpp" line="623"/>
        <source>Frequently Used</source>
        <translation>Frequently Used</translation>
    </message>
    <message>
        <location filename="../src/ui/emoji_picker/emoji_picker_popup.cpp" line="661"/>
        <source>Custom</source>
        <translation>Custom</translation>
    </message>
</context>
<context>
    <name>ForwardDialog</name>
    <message>
        <location filename="../src/ui/forward_dialog/forward_dialog.cpp" line="24"/>
        <source>Forward this message</source>
        <translation>Forward this message</translation>
    </message>
    <message>
        <location filename="../src/ui/forward_dialog/forward_dialog.cpp" line="34"/>
        <source>Add a message, if you'd like.</source>
        <translation>Add a message, if you'd like.</translation>
    </message>
    <message>
        <location filename="../src/ui/forward_dialog/forward_dialog.cpp" line="172"/>
        <source>Copy Link</source>
        <translation>Copy Link</translation>
    </message>
    <message>
        <location filename="../src/ui/forward_dialog/forward_dialog.cpp" line="173"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="../src/ui/forward_dialog/forward_dialog.cpp" line="174"/>
        <source>Forward</source>
        <translation>Forward</translation>
    </message>
</context>
<context>
    <name>GifGrid</name>
    <message>
        <location filename="../src/ui/gif_picker/gif_picker_popup.cpp" line="391"/>
        <source>Search GIFs</source>
        <translation>Search GIFs</translation>
    </message>
    <message>
        <location filename="../src/ui/gif_picker/gif_picker_popup.cpp" line="448"/>
        <source>No GIFs found.</source>
        <translation>No GIFs found.</translation>
    </message>
    <message>
        <location filename="../src/ui/gif_picker/gif_picker_popup.cpp" line="496"/>
        <source>Searching GIFs needs a GIPHY API key.

Create a free one — it takes a minute — then paste it below. You can change it later in Settings → System.</source>
        <translation>Searching GIFs needs a GIPHY API key.

Create a free one — it takes a minute — then paste it below. You can change it later in Settings → System.</translation>
    </message>
    <message>
        <location filename="../src/ui/gif_picker/gif_picker_popup.cpp" line="504"/>
        <source>Get a free GIPHY key…</source>
        <translation>Get a free GIPHY key…</translation>
    </message>
    <message>
        <location filename="../src/ui/gif_picker/gif_picker_popup.cpp" line="515"/>
        <source>Paste your GIPHY API key</source>
        <translation>Paste your GIPHY API key</translation>
    </message>
    <message>
        <location filename="../src/ui/gif_picker/gif_picker_popup.cpp" line="526"/>
        <source>Save</source>
        <translation>Save</translation>
    </message>
    <message>
        <location filename="../src/ui/gif_picker/gif_picker_popup.cpp" line="548"/>
        <source>Paste a key first.</source>
        <translation>Paste a key first.</translation>
    </message>
    <message>
        <location filename="../src/ui/gif_picker/gif_picker_popup.cpp" line="664"/>
        <source>Searching…</source>
        <translation>Searching…</translation>
    </message>
    <message>
        <location filename="../src/ui/gif_picker/gif_picker_popup.cpp" line="675"/>
        <source>Searching…</source>
        <translation>Searching…</translation>
    </message>
</context>
<context>
    <name>HuddleBanner</name>
    <message>
        <location filename="../src/ui/huddle_banner/huddle_banner.cpp" line="30"/>
        <source>A huddle is happening</source>
        <translation>A huddle is happening</translation>
    </message>
    <message>
        <location filename="../src/ui/huddle_banner/huddle_banner.cpp" line="33"/>
        <source>Join</source>
        <translation>Join</translation>
    </message>
    <message>
        <location filename="../src/ui/huddle_banner/huddle_banner.cpp" line="63"/>
        <source>Opens the huddle in Slack for web</source>
        <translation>Opens the huddle in Slack for web</translation>
    </message>
</context>
<context>
    <name>ImageViewerOverlay</name>
    <message>
        <location filename="../src/ui/image_viewer/image_viewer.cpp" line="46"/>
        <source>Download</source>
        <translation>Download</translation>
    </message>
    <message>
        <location filename="../src/ui/image_viewer/image_viewer.cpp" line="47"/>
        <source>Forward</source>
        <translation>Forward</translation>
    </message>
    <message>
        <location filename="../src/ui/image_viewer/image_viewer.cpp" line="48"/>
        <source>Open in browser</source>
        <translation>Open in browser</translation>
    </message>
    <message>
        <location filename="../src/ui/image_viewer/image_viewer.cpp" line="49"/>
        <source>More actions</source>
        <translation>More actions</translation>
    </message>
    <message>
        <location filename="../src/ui/image_viewer/image_viewer.cpp" line="50"/>
        <source>Close</source>
        <translation>Close</translation>
    </message>
    <message>
        <location filename="../src/ui/image_viewer/image_viewer.cpp" line="156"/>
        <source>Loading image…</source>
        <translation>Loading image…</translation>
    </message>
</context>
<context>
    <name>ImapAddAccountDialog</name>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="21"/>
        <source>Add email account</source>
        <translation>Add email account</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="35"/>
        <source>IMAP server</source>
        <translation>IMAP server</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="37"/>
        <source>Detect</source>
        <translation>Detect</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="47"/>
        <source>Sign in with Google</source>
        <translation>Sign in with Google</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="53"/>
        <source>Password or app password</source>
        <translation>Password or app password</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="70"/>
        <source>Continue</source>
        <translation>Continue</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="71"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="93"/>
        <source>Enter a valid email address.</source>
        <translation>Enter a valid email address.</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="107"/>
        <source>Add</source>
        <translation>Add</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="126"/>
        <source>Add</source>
        <translation>Add</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="132"/>
        <source>Sign in with %1</source>
        <translation>Sign in with %1</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="150"/>
        <source>%1 needs an app password to sign in</source>
        <translation>%1 needs an app password to sign in</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="152"/>
        <source>%1 needs an app password</source>
        <translation>%1 needs an app password</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="167"/>
        <source>Server: %1</source>
        <translation>Server: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="174"/>
        <source>Couldn't detect the server — enter it manually.</source>
        <translation>Couldn't detect the server — enter it manually.</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="194"/>
        <source>Detecting…</source>
        <translation>Detecting…</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="202"/>
        <source>Enter the IMAP server or click Detect.</source>
        <translation>Enter the IMAP server or click Detect.</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="206"/>
        <source>Enter your password.</source>
        <translation>Enter your password.</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="216"/>
        <source>Checking…</source>
        <translation>Checking…</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="224"/>
        <source>Sign-in failed: %1</source>
        <translation>Sign-in failed: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="248"/>
        <source>Opening your browser to sign in…</source>
        <translation>Opening your browser to sign in…</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="256"/>
        <source>Sign-in failed: no access token returned.</source>
        <translation>Sign-in failed: no access token returned.</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="271"/>
        <source>Checking…</source>
        <translation>Checking…</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="275"/>
        <source>Sign-in failed: %1</source>
        <translation>Sign-in failed: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/imap_add_account/imap_add_account_dialog.cpp" line="286"/>
        <source>Sign-in failed: %1</source>
        <translation>Sign-in failed: %1</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../src/ui/main_window.cpp" line="470"/>
        <source>Log in to workspace</source>
        <translation>Log in to workspace</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1551"/>
        <source>Convert to session</source>
        <translation>Convert to session</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1552"/>
        <source>Add one workspace with your Slack session first — its cookie is reused for the rest.</source>
        <translation>Add one workspace with your Slack session first — its cookie is reused for the rest.</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1559"/>
        <source>Convert to session</source>
        <translation>Convert to session</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1559"/>
        <source>All Slack workspaces already use your session.</source>
        <translation>All Slack workspaces already use your session.</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1573"/>
        <source>Convert to session</source>
        <translation>Convert to session</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1574"/>
        <source>Couldn't convert your workspaces: %1</source>
        <translation>Couldn't convert your workspaces: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1655"/>
        <source>Login failed</source>
        <translation>Login failed</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1655"/>
        <source>This service is not supported.</source>
        <translation>This service is not supported.</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1684"/>
        <source>Login failed</source>
        <translation>Login failed</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1815"/>
        <source>Message</source>
        <translation>Message</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1815"/>
        <source>Message %1</source>
        <translation>Message %1</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2034"/>
        <source>Message</source>
        <translation>Message</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2034"/>
        <source>Message %1</source>
        <translation>Message %1</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2304"/>
        <source>Someone</source>
        <translation>Someone</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2443"/>
        <source>Someone</source>
        <translation>Someone</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2449"/>
        <source>Started a huddle</source>
        <translation>Started a huddle</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2452"/>
        <source>%1 started a huddle</source>
        <translation>%1 started a huddle</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2482"/>
        <source>Join</source>
        <translation>Join</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2552"/>
        <source>Reminder</source>
        <translation>Reminder</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2552"/>
        <source>Reminder — %1</source>
        <translation>Reminder — %1</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2571"/>
        <source>You asked to be reminded about a message.</source>
        <translation>You asked to be reminded about a message.</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2626"/>
        <source>Sample User</source>
        <translation>Sample User</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2634"/>
        <source>Hey — do you have a minute?</source>
        <translation>Hey — do you have a minute?</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2638"/>
        <source>%1: Heads up, the deploy is going out at 3pm</source>
        <translation>%1: Heads up, the deploy is going out at 3pm</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2642"/>
        <source>%1 started a huddle</source>
        <translation>%1 started a huddle</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2647"/>
        <source>Join</source>
        <translation>Join</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2691"/>
        <source>Session expired</source>
        <translation>Session expired</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2694"/>
        <source>Your session has expired. Click to sign in again.</source>
        <translation>Your session has expired. Click to sign in again.</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2695"/>
        <source>Your %1 session has expired. Click to sign in again.</source>
        <translation>Your %1 session has expired. Click to sign in again.</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2886"/>
        <source>Workspace admin</source>
        <translation>Workspace admin</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2892"/>
        <source>Unmute</source>
        <translation>Unmute</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2892"/>
        <source>Mute</source>
        <translation>Mute</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2897"/>
        <source>Log out</source>
        <translation>Log out</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2897"/>
        <source>Log out from %1</source>
        <translation>Log out from %1</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2956"/>
        <source>Settings</source>
        <translation>Settings</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2963"/>
        <source>Reset window size</source>
        <translation>Reset window size</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="2968"/>
        <source>Quit</source>
        <translation>Quit</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="3057"/>
        <source>Couldn't apply the label.</source>
        <translation>Couldn't apply the label.</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="3455"/>
        <source>Opens the huddle in Slack for web</source>
        <translation>Opens the huddle in Slack for web</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="3465"/>
        <source>Unstar conversation</source>
        <translation>Unstar conversation</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="3465"/>
        <source>Star conversation</source>
        <translation>Star conversation</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="3476"/>
        <source>Search messages</source>
        <translation>Search messages</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="3855"/>
        <source>Message</source>
        <translation>Message</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="3855"/>
        <source>Message %1</source>
        <translation>Message %1</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1698"/>
        <source>You appear away to others — no official Slack client is connected</source>
        <translation>You appear away to others — no official Slack client is connected</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1702"/>
        <source>Active</source>
        <translation>Active</translation>
    </message>
    <message>
        <location filename="../src/ui/main_window.cpp" line="1704"/>
        <source>Away</source>
        <translation>Away</translation>
    </message>
</context>
<context>
    <name>MentionPopup</name>
    <message>
        <location filename="../src/ui/mention_popup/mention_popup.cpp" line="442"/>
        <source>(you)</source>
        <translation>(you)</translation>
    </message>
    <message>
        <location filename="../src/ui/mention_popup/mention_popup.cpp" line="125"/>
        <source>Enter</source>
        <translation>Enter</translation>
    </message>
    <message>
        <location filename="../src/ui/mention_popup/mention_popup.cpp" line="154"/>
        <source>APP</source>
        <translation>APP</translation>
    </message>
</context>
<context>
    <name>MessageListWidget</name>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2023"/>
        <source>Open full table</source>
        <translation>Open full table</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2281"/>
        <source>Reply in thread</source>
        <translation>Reply in thread</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2298"/>
        <source>Unmute thread</source>
        <translation>Unmute thread</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2298"/>
        <source>Mute thread</source>
        <translation>Mute thread</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2316"/>
        <source>Edit message</source>
        <translation>Edit message</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2330"/>
        <source>Copy link</source>
        <translation>Copy link</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2340"/>
        <source>Copy message</source>
        <translation>Copy message</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2354"/>
        <source>Unpin from channel</source>
        <translation>Unpin from channel</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2371"/>
        <source>Pin to channel</source>
        <translation>Pin to channel</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2395"/>
        <source>Remove reminder</source>
        <translation>Remove reminder</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2407"/>
        <source>Remind me</source>
        <translation>Remind me</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2420"/>
        <source>Forward message</source>
        <translation>Forward message</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2434"/>
        <source>Move to thread…</source>
        <translation>Move to thread…</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2444"/>
        <source>Summarize down</source>
        <translation>Summarize down</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2455"/>
        <source>Delete message…</source>
        <translation>Delete message…</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2492"/>
        <source>Remind me about this…</source>
        <translation>Remind me about this…</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2493"/>
        <source>In 20 minutes</source>
        <translation>In 20 minutes</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2494"/>
        <source>In 1 hour</source>
        <translation>In 1 hour</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2495"/>
        <source>In 3 hours</source>
        <translation>In 3 hours</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2497"/>
        <source>Tomorrow</source>
        <translation>Tomorrow</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2500"/>
        <source>Next week</source>
        <translation>Next week</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2504"/>
        <source>Custom…</source>
        <translation>Custom…</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2528"/>
        <source>Summaries need an AI provider. Connect one in Settings → AI assistance.</source>
        <translation>Summaries need an AI provider. Connect one in Settings → AI assistance.</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2571"/>
        <source>You</source>
        <translation>You</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2780"/>
        <source>Open link</source>
        <translation>Open link</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2785"/>
        <source>Copy link</source>
        <translation>Copy link</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2852"/>
        <source>Slack doesn't let third-party apps press bot buttons, we are working on a workaround</source>
        <translation>Slack doesn't let third-party apps press bot buttons, we are working on a workaround</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2867"/>
        <source>No email app — address copied</source>
        <translation>No email app — address copied</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2903"/>
        <source>file</source>
        <translation>file</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2905"/>
        <source>Save file</source>
        <translation>Save file</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2914"/>
        <source>Downloading %1</source>
        <translation>Downloading %1</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2956"/>
        <source>image</source>
        <translation>image</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="2957"/>
        <source>Copying %1</source>
        <translation>Copying %1</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3007"/>
        <source>Preview</source>
        <translation>Preview</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3013"/>
        <source>Copy link to image</source>
        <translation>Copy link to image</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3013"/>
        <source>Copy link to file</source>
        <translation>Copy link to file</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3023"/>
        <source>Copy full image</source>
        <translation>Copy full image</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3037"/>
        <source>Delete image…</source>
        <translation>Delete image…</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3037"/>
        <source>Delete file…</source>
        <translation>Delete file…</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3055"/>
        <source>file</source>
        <translation>file</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3057"/>
        <source>Downloading %1</source>
        <translation>Downloading %1</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3064"/>
        <source>This file is empty</source>
        <translation>This file is empty</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3069"/>
        <source>Showing the first %1 of %2 rows</source>
        <translation>Showing the first %1 of %2 rows</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3273"/>
        <source>Download failed</source>
        <translation>Download failed</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3279"/>
        <source>Could not save the file</source>
        <translation>Could not save the file</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3287"/>
        <source>Download failed</source>
        <translation>Download failed</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3295"/>
        <source>%1 at %2</source>
        <translation>%1 at %2</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3297"/>
        <source>%1 · transcribed by %2</source>
        <translation>%1 · transcribed by %2</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3344"/>
        <source>%1 at %2</source>
        <translation>%1 at %2</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3346"/>
        <source>%1 · transcribed by %2</source>
        <translation>%1 · transcribed by %2</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3387"/>
        <source>No speech was recognised</source>
        <translation>No speech was recognised</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3393"/>
        <source>Couldn't transcribe: %1</source>
        <translation>Couldn't transcribe: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3403"/>
        <source>Transcription needs an AI provider. Connect one in Settings → AI assistance.</source>
        <translation>Transcription needs an AI provider. Connect one in Settings → AI assistance.</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3409"/>
        <source>%1 does not support speech-to-text. Pick an OpenAI-compatible provider in Settings → AI assistance.</source>
        <translation>%1 does not support speech-to-text. Pick an OpenAI-compatible provider in Settings → AI assistance.</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3419"/>
        <source>Could not read the file</source>
        <translation>Could not read the file</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3426"/>
        <source>Download failed</source>
        <translation>Download failed</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3441"/>
        <source>Download failed</source>
        <translation>Download failed</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3453"/>
        <source>Download failed</source>
        <translation>Download failed</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3925"/>
        <source>Add reaction</source>
        <translation>Add reaction</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3925"/>
        <source>Forward message</source>
        <translation>Forward message</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3925"/>
        <source>More actions</source>
        <translation>More actions</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3934"/>
        <source>Download</source>
        <translation>Download</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3934"/>
        <source>Share</source>
        <translation>Share</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3934"/>
        <source>More actions</source>
        <translation>More actions</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3943"/>
        <source>Transcribe with AI</source>
        <translation>Transcribe with AI</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list.cpp" line="3977"/>
        <source>Remove preview</source>
        <translation>Remove preview</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="87"/>
        <source>Oh my gosh, I really apologize, but your company is a reaaaly active Slack user. Still loading...</source>
        <translation>Oh my gosh, I really apologize, but your company is a reaaaly active Slack user. Still loading...</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="90"/>
        <source>Oh, you must have a lot of co-workers and messages! Still loading...</source>
        <translation>Oh, you must have a lot of co-workers and messages! Still loading...</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="92"/>
        <source>Loading your stuff...</source>
        <translation>Loading your stuff...</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="119"/>
        <source>No messages yet</source>
        <translation>No messages yet</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="190"/>
        <source>Open full table</source>
        <translation>Open full table</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="270"/>
        <source>Pinned by %1</source>
        <translation>Pinned by %1</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="270"/>
        <source>Pinned</source>
        <translation>Pinned</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="305"/>
        <source>Reminder — past due</source>
        <translation>Reminder — past due</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="306"/>
        <source>Reminder — %1</source>
        <translation>Reminder — %1</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="662"/>
        <source>(edited)</source>
        <translation>(edited)</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="673"/>
        <source>APP</source>
        <translation>APP</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="685"/>
        <source>EXT</source>
        <translation>EXT</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="761"/>
        <source>Unknown user</source>
        <translation>Unknown user</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="786"/>
        <source>APP</source>
        <translation>APP</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="810"/>
        <source>Posted in %1</source>
        <translation>Posted in %1</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="1270"/>
        <source>Loading image…</source>
        <translation>Loading image…</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="1838"/>
        <source>1 reply</source>
        <translation>1 reply</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="1838"/>
        <source>%1 replies</source>
        <translation>%1 replies</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="1861"/>
        <source>Close thread</source>
        <translation>Close thread</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="1878"/>
        <source>View thread</source>
        <translation>View thread</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="1892"/>
        <source>Last reply</source>
        <translation>Last reply</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="1892"/>
        <source>Last reply %1</source>
        <translation>Last reply %1</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="2127"/>
        <source>Loading replies…</source>
        <translation>Loading replies…</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="2151"/>
        <source>Reply to thread</source>
        <translation>Reply to thread</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_list_paint.cpp" line="2160"/>
        <source>Reply to thread</source>
        <translation>Reply to thread</translation>
    </message>
</context>
<context>
    <name>MsgRender</name>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="196"/>
        <source>Today</source>
        <translation>Today</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="198"/>
        <source>Yesterday</source>
        <translation>Yesterday</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="214"/>
        <source>today at %1</source>
        <translation>today at %1</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="216"/>
        <source>yesterday at %1</source>
        <translation>yesterday at %1</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="217"/>
        <source>%1 at %2</source>
        <translation>%1 at %2</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="229"/>
        <source>yesterday at %1</source>
        <translation>yesterday at %1</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="232"/>
        <source>%1 at %2</source>
        <translation>%1 at %2</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="234"/>
        <source>%1 at %2</source>
        <translation>%1 at %2</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="279"/>
        <source>group message</source>
        <translation>group message</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="293"/>
        <source>%1 in %2</source>
        <translation>%1 in %2</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="299"/>
        <source>message</source>
        <translation>message</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="598"/>
        <source>GIF</source>
        <translation>GIF</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="1506"/>
        <source>Show less</source>
        <translation>Show less</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="1507"/>
        <source>Show more</source>
        <translation>Show more</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="1855"/>
        <source>Loading…</source>
        <translation>Loading…</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="1952"/>
        <source>View transcript</source>
        <translation>View transcript</translation>
    </message>
    <message>
        <location filename="../src/ui/message_list/message_render.cpp" line="2006"/>
        <source>View transcript</source>
        <translation>View transcript</translation>
    </message>
</context>
<context>
    <name>MoveToThreadDialog</name>
    <message>
        <location filename="../src/ui/move_to_thread_dialog/move_to_thread_dialog.cpp" line="22"/>
        <source>Move to thread</source>
        <translation>Move to thread</translation>
    </message>
    <message>
        <location filename="../src/ui/move_to_thread_dialog/move_to_thread_dialog.cpp" line="32"/>
        <source>Pick a thread in this channel. The message is posted there again by you, and the original is deleted.</source>
        <translation>Pick a thread in this channel. The message is posted there again by you, and the original is deleted.</translation>
    </message>
    <message>
        <location filename="../src/ui/move_to_thread_dialog/move_to_thread_dialog.cpp" line="40"/>
        <source>Filter threads…</source>
        <translation>Filter threads…</translation>
    </message>
    <message>
        <location filename="../src/ui/move_to_thread_dialog/move_to_thread_dialog.cpp" line="67"/>
        <source>Add a note with the original author and time</source>
        <translation>Add a note with the original author and time</translation>
    </message>
    <message>
        <location filename="../src/ui/move_to_thread_dialog/move_to_thread_dialog.cpp" line="71"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="../src/ui/move_to_thread_dialog/move_to_thread_dialog.cpp" line="72"/>
        <source>Move</source>
        <translation>Move</translation>
    </message>
    <message>
        <location filename="../src/ui/move_to_thread_dialog/move_to_thread_dialog.cpp" line="97"/>
        <source>(no text)</source>
        <translation>(no text)</translation>
    </message>
    <message>
        <location filename="../src/ui/move_to_thread_dialog/move_to_thread_dialog.cpp" line="99"/>
        <source>1 reply</source>
        <translation>1 reply</translation>
    </message>
    <message>
        <location filename="../src/ui/move_to_thread_dialog/move_to_thread_dialog.cpp" line="99"/>
        <source>%1 replies</source>
        <translation>%1 replies</translation>
    </message>
    <message>
        <location filename="../src/ui/move_to_thread_dialog/move_to_thread_dialog.cpp" line="120"/>
        <source>No threads in this channel's loaded history yet.</source>
        <translation>No threads in this channel's loaded history yet.</translation>
    </message>
    <message>
        <location filename="../src/ui/move_to_thread_dialog/move_to_thread_dialog.cpp" line="121"/>
        <source>No threads match.</source>
        <translation>No threads match.</translation>
    </message>
</context>
<context>
    <name>ParallelUsageBanner</name>
    <message>
        <location filename="../src/ui/parallel_usage_banner/parallel_usage_banner.cpp" line="34"/>
        <source>The same app keys are running on another device and keep interrupting your Slack connection.</source>
        <translation>The same app keys are running on another device and keep interrupting your Slack connection.</translation>
    </message>
    <message>
        <location filename="../src/ui/parallel_usage_banner/parallel_usage_banner.cpp" line="37"/>
        <source>How to solve this?</source>
        <translation>How to solve this?</translation>
    </message>
</context>
<context>
    <name>ProfileAvatarWidget</name>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="98"/>
        <source>Change photo</source>
        <translation>Change photo</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="118"/>
        <source>Profile</source>
        <translation>Profile</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="142"/>
        <source>Name</source>
        <translation>Name</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="144"/>
        <source>Your display name</source>
        <translation>Your display name</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="145"/>
        <source>Email</source>
        <translation>Email</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="146"/>
        <source>name@example.com</source>
        <translation>name@example.com</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="147"/>
        <source>Phone</source>
        <translation>Phone</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="148"/>
        <source>Optional</source>
        <translation>Optional</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="159"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="160"/>
        <source>Save Changes</source>
        <translation>Save Changes</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="250"/>
        <source>Choose a profile photo</source>
        <translation>Choose a profile photo</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="250"/>
        <source>Images (*.png *.jpg *.jpeg *.gif)</source>
        <translation>Images (*.png *.jpg *.jpeg *.gif)</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="255"/>
        <source>Uploading photo…</source>
        <translation>Uploading photo…</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="260"/>
        <source>Could not upload photo: %1</source>
        <translation>Could not upload photo: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="263"/>
        <source>Photo updated.</source>
        <translation>Photo updated.</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="292"/>
        <source>Saving…</source>
        <translation>Saving…</translation>
    </message>
    <message>
        <location filename="../src/ui/profile_dialog/profile_dialog.cpp" line="296"/>
        <source>Could not save: %1</source>
        <translation>Could not save: %1</translation>
    </message>
</context>
<context>
    <name>QuickSwitcherDialog</name>
    <message>
        <location filename="../src/ui/quick_switcher/quick_switcher_dialog.cpp" line="80"/>
        <source>Jump to a conversation…</source>
        <translation>Jump to a conversation…</translation>
    </message>
    <message>
        <location filename="../src/ui/quick_switcher/quick_switcher_dialog.cpp" line="106"/>
        <source>No conversations match.</source>
        <translation>No conversations match.</translation>
    </message>
    <message>
        <location filename="../src/ui/quick_switcher/quick_switcher_dialog.cpp" line="120"/>
        <source>%1 to move · %2 to switch workspace · %3 to open</source>
        <translation>%1 to move · %2 to switch workspace · %3 to open</translation>
    </message>
    <message>
        <location filename="../src/ui/quick_switcher/quick_switcher_dialog.cpp" line="121"/>
        <source>%1 to move · %2 to open</source>
        <translation>%1 to move · %2 to open</translation>
    </message>
    <message>
        <location filename="../src/ui/quick_switcher/quick_switcher_dialog.cpp" line="252"/>
        <source>No matches in %1. Other workspaces have some.</source>
        <translation>No matches in %1. Other workspaces have some.</translation>
    </message>
    <message>
        <location filename="../src/ui/quick_switcher/quick_switcher_dialog.cpp" line="254"/>
        <source>No conversations match.</source>
        <translation>No conversations match.</translation>
    </message>
</context>
<context>
    <name>ReminderDialog</name>
    <message>
        <location filename="../src/ui/reminder_dialog/reminder_dialog.cpp" line="15"/>
        <source>Reminder</source>
        <translation>Reminder</translation>
    </message>
    <message>
        <location filename="../src/ui/reminder_dialog/reminder_dialog.cpp" line="26"/>
        <source>When</source>
        <translation>When</translation>
    </message>
    <message>
        <location filename="../src/ui/reminder_dialog/reminder_dialog.cpp" line="36"/>
        <source>Time</source>
        <translation>Time</translation>
    </message>
    <message>
        <location filename="../src/ui/reminder_dialog/reminder_dialog.cpp" line="46"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="../src/ui/reminder_dialog/reminder_dialog.cpp" line="47"/>
        <source>Save</source>
        <translation>Save</translation>
    </message>
</context>
<context>
    <name>RenameConversationDialog</name>
    <message>
        <location filename="../src/ui/rename_conversation_dialog/rename_conversation_dialog.cpp" line="19"/>
        <source>Name conversation</source>
        <translation>Name conversation</translation>
    </message>
    <message>
        <location filename="../src/ui/rename_conversation_dialog/rename_conversation_dialog.cpp" line="24"/>
        <source>Name</source>
        <translation>Name</translation>
    </message>
    <message>
        <location filename="../src/ui/rename_conversation_dialog/rename_conversation_dialog.cpp" line="38"/>
        <source>Only you see this name. Leave it empty to show the members' names again.</source>
        <translation>Only you see this name. Leave it empty to show the members' names again.</translation>
    </message>
    <message>
        <location filename="../src/ui/rename_conversation_dialog/rename_conversation_dialog.cpp" line="42"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="../src/ui/rename_conversation_dialog/rename_conversation_dialog.cpp" line="43"/>
        <source>Save</source>
        <translation>Save</translation>
    </message>
</context>
<context>
    <name>SavedMessagesPage</name>
    <message>
        <location filename="../src/ui/saved_page/saved_messages_page.cpp" line="121"/>
        <source>No preview available</source>
        <translation>No preview available</translation>
    </message>
    <message>
        <location filename="../src/ui/saved_page/saved_messages_page.cpp" line="150"/>
        <source>Message</source>
        <translation>Message</translation>
    </message>
    <message>
        <location filename="../src/ui/saved_page/saved_messages_page.cpp" line="221"/>
        <source>Remove</source>
        <translation>Remove</translation>
    </message>
    <message>
        <location filename="../src/ui/saved_page/saved_messages_page.cpp" line="289"/>
        <source>Reminder set for %1</source>
        <translation>Reminder set for %1</translation>
    </message>
    <message>
        <location filename="../src/ui/saved_page/saved_messages_page.cpp" line="322"/>
        <source>Saved messages</source>
        <translation>Saved messages</translation>
    </message>
    <message>
        <location filename="../src/ui/saved_page/saved_messages_page.cpp" line="409"/>
        <source>Messages you set reminders on will appear here.</source>
        <translation>Messages you set reminders on will appear here.</translation>
    </message>
</context>
<context>
    <name>SearchWidget</name>
    <message>
        <location filename="../src/ui/search/search_widget.cpp" line="77"/>
        <source>Search messages…</source>
        <translation>Search messages…</translation>
    </message>
    <message>
        <location filename="../src/ui/search/search_widget.cpp" line="234"/>
        <source>Search messages</source>
        <translation>Search messages</translation>
    </message>
    <message>
        <location filename="../src/ui/search/search_widget.cpp" line="245"/>
        <source>Close search</source>
        <translation>Close search</translation>
    </message>
    <message>
        <location filename="../src/ui/search/search_widget.cpp" line="313"/>
        <source>Searching…</source>
        <translation>Searching…</translation>
    </message>
    <message>
        <location filename="../src/ui/search/search_widget.cpp" line="388"/>
        <source>No results found.</source>
        <translation>No results found.</translation>
    </message>
    <message>
        <location filename="../src/ui/search/search_widget.cpp" line="402"/>
        <source>Unknown channel</source>
        <translation>Unknown channel</translation>
    </message>
</context>
<context>
    <name>SessionImportDialog</name>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="24"/>
        <source>The Slack desktop app wasn't found on this computer.</source>
        <translation>The Slack desktop app wasn't found on this computer.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="26"/>
        <source>Couldn't read Slack's data — try quitting the Slack app first.</source>
        <translation>Couldn't read Slack's data — try quitting the Slack app first.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="28"/>
        <source>Couldn't read Slack's saved session automatically.</source>
        <translation>Couldn't read Slack's saved session automatically.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="30"/>
        <source>Automatic import isn't available in this build.</source>
        <translation>Automatic import isn't available in this build.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="31"/>
        <source>Automatic import didn't work.</source>
        <translation>Automatic import didn't work.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="37"/>
        <source>No supported browser was found — browser sign-in needs Chrome, Chromium, Brave, Edge or Vivaldi.</source>
        <translation>No supported browser was found — browser sign-in needs Chrome, Chromium, Brave, Edge or Vivaldi.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="42"/>
        <source>Couldn't start your browser.</source>
        <translation>Couldn't start your browser.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="44"/>
        <source>Couldn't read the session back from the browser window.</source>
        <translation>Couldn't read the session back from the browser window.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="46"/>
        <source>Browser sign-in was cancelled.</source>
        <translation>Browser sign-in was cancelled.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="48"/>
        <source>Browser sign-in timed out.</source>
        <translation>Browser sign-in timed out.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="49"/>
        <source>Browser sign-in didn't work.</source>
        <translation>Browser sign-in didn't work.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="76"/>
        <source>Add Slack workspace with a session token</source>
        <translation>Add Slack workspace with a session token</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="86"/>
        <source>Log in to Slack in a browser window and msga uses that session instead of app keys — so it runs on your account's own rate limits and avoids the shared-key timeouts. New messages arrive by polling (there's no live push this way).</source>
        <translation>Log in to Slack in a browser window and msga uses that session instead of app keys — so it runs on your account's own rate limits and avoids the shared-key timeouts. New messages arrive by polling (there's no live push this way).</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="92"/>
        <source>Sign in with your existing Slack session instead of app keys — it uses your account's own rate limits, so it avoids the shared-key timeouts. New messages arrive by polling (there's no live push this way).</source>
        <translation>Sign in with your existing Slack session instead of app keys — it uses your account's own rate limits, so it avoids the shared-key timeouts. New messages arrive by polling (there's no live push this way).</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="103"/>
        <source>Sign in with %1</source>
        <translation>Sign in with %1</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="114"/>
        <source>Import from local Slack</source>
        <translation>Import from local Slack</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="123"/>
        <source>Paste a session cookie instead</source>
        <translation>Paste a session cookie instead</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="141"/>
        <source>1. Sign in to the workspace in your browser.
2. Open developer tools (F12) → Application → Cookies → https://app.slack.com, and copy the value of the cookie named “d” (it starts with xoxd-) into Cookie. Browsers hide this cookie from scripts, so it has to be copied by hand.
3. Enter your workspace address.</source>
        <translation>1. Sign in to the workspace in your browser.
2. Open developer tools (F12) → Application → Cookies → https://app.slack.com, and copy the value of the cookie named “d” (it starts with xoxd-) into Cookie. Browsers hide this cookie from scripts, so it has to be copied by hand.
3. Enter your workspace address.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="156"/>
        <source>Cookie</source>
        <translation>Cookie</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="164"/>
        <source>Workspace</source>
        <translation>Workspace</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="178"/>
        <source>Use app keys (OAuth) instead</source>
        <translation>Use app keys (OAuth) instead</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="188"/>
        <source>Add workspace</source>
        <translation>Add workspace</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="190"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="209"/>
        <source>Opening a browser window…</source>
        <translation>Opening a browser window…</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="237"/>
        <source>Signed in — enter your workspace address.</source>
        <translation>Signed in — enter your workspace address.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="248"/>
        <source>Importing from local Slack…</source>
        <translation>Importing from local Slack…</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="260"/>
        <source>Found your Slack session — enter your workspace address.</source>
        <translation>Found your Slack session — enter your workspace address.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="271"/>
        <source>Paste the “d” cookie value.</source>
        <translation>Paste the “d” cookie value.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="275"/>
        <source>Enter your workspace address (e.g. myteam.slack.com).</source>
        <translation>Enter your workspace address (e.g. myteam.slack.com).</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="287"/>
        <source>Verifying your session…</source>
        <translation>Verifying your session…</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="300"/>
        <source>Couldn't verify that session. Check the cookie and workspace address and try again.</source>
        <translation>Couldn't verify that session. Check the cookie and workspace address and try again.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="305"/>
        <source>That session was rejected — the cookie may have expired. Sign in to Slack again and copy a fresh cookie.</source>
        <translation>That session was rejected — the cookie may have expired. Sign in to Slack again and copy a fresh cookie.</translation>
    </message>
    <message>
        <location filename="../src/ui/session_import_dialog/session_import_dialog.cpp" line="312"/>
        <source>That workspace loaded but Slack didn't hand out a session token — the cookie has probably expired, or it belongs to an account without access to that workspace. Sign in to Slack again and copy a fresh cookie.</source>
        <translation>That workspace loaded but Slack didn't hand out a session token — the cookie has probably expired, or it belongs to an account without access to that workspace. Sign in to Slack again and copy a fresh cookie.</translation>
    </message>
</context>
<context>
    <name>CustomThemeEditor</name>
    <message>
        <location filename="../src/ui/settings/custom_theme_editor.cpp" line="29"/>
        <source>Paste a Slack theme (colour list or JSON)</source>
        <translation>Paste a Slack theme (colour list or JSON)</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/custom_theme_editor.cpp" line="30"/>
        <source>Import</source>
        <translation>Import</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/custom_theme_editor.cpp" line="39"/>
        <source>Darker sidebar</source>
        <translation>Darker sidebar</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/custom_theme_editor.cpp" line="40"/>
        <source>Window gradient</source>
        <translation>Window gradient</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/custom_theme_editor.cpp" line="65"/>
        <source>Copy theme</source>
        <translation>Copy theme</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/custom_theme_editor.cpp" line="68"/>
        <source>Use my Slack theme</source>
        <translation>Use my Slack theme</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/custom_theme_editor.cpp" line="77"/>
        <source>Reading your Slack theme…</source>
        <translation>Reading your Slack theme…</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/custom_theme_editor.cpp" line="122"/>
        <source>Low contrast: sidebar text may be hard to read</source>
        <translation>Low contrast: sidebar text may be hard to read</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/custom_theme_editor.cpp" line="130"/>
        <source>Not a Slack theme. Paste 8 or 10 colours separated by commas, or theme JSON.</source>
        <translation>Not a Slack theme. Paste 8 or 10 colours separated by commas, or theme JSON.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/custom_theme_editor.cpp" line="137"/>
        <source>Theme imported</source>
        <translation>Theme imported</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/custom_theme_editor.cpp" line="145"/>
        <source>Theme copied: paste it into Slack's Import theme field</source>
        <translation>Theme copied: paste it into Slack's Import theme field</translation>
    </message>
</context>
<context>
    <name>SettingsDialog</name>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="125"/>
        <source>RAM used: %1</source>
        <translation>RAM used: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="157"/>
        <source>Settings</source>
        <translation>Settings</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="177"/>
        <source>Appearance</source>
        <translation>Appearance</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="178"/>
        <source>Notifications</source>
        <translation>Notifications</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="179"/>
        <source>AI assistance</source>
        <translation>AI assistance</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="180"/>
        <source>Storage</source>
        <translation>Storage</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="181"/>
        <source>System</source>
        <translation>System</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="182"/>
        <source>About</source>
        <translation>About</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="198"/>
        <source>Color mode</source>
        <translation>Color mode</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="208"/>
        <source>Light</source>
        <translation>Light</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="209"/>
        <source>Dark</source>
        <translation>Dark</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="210"/>
        <source>System</source>
        <translation>System</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="246"/>
        <source>Color theme</source>
        <translation>Color theme</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="251"/>
        <source>Purple</source>
        <translation>Purple</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="252"/>
        <source>Charcoal</source>
        <translation>Charcoal</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="253"/>
        <source>Blue</source>
        <translation>Blue</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="254"/>
        <source>Green</source>
        <translation>Green</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="255"/>
        <source>Custom</source>
        <translation>Custom</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="343"/>
        <source>Light theme</source>
        <translation>Light theme</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="344"/>
        <source>Dark theme</source>
        <translation>Dark theme</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="351"/>
        <source>Custom theme</source>
        <translation>Custom theme</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="373"/>
        <source>Font size</source>
        <translation>Font size</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="383"/>
        <source>Small</source>
        <translation>Small</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="384"/>
        <source>Medium (default)</source>
        <translation>Medium (default)</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="385"/>
        <source>Large</source>
        <translation>Large</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="400"/>
        <source>Language</source>
        <translation>Language</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="411"/>
        <source>App language</source>
        <translation>App language</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="419"/>
        <source>System default</source>
        <translation>System default</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="428"/>
        <source>The new language will be applied the next time MSGA starts.
Time and date formats update immediately.</source>
        <translation>The new language will be applied the next time MSGA starts.
Time and date formats update immediately.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="444"/>
        <source>Date/Time</source>
        <translation>Date/Time</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="454"/>
        <source>12-hour clock (2:34 PM)</source>
        <translation>12-hour clock (2:34 PM)</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="455"/>
        <source>24-hour clock (14:34)</source>
        <translation>24-hour clock (14:34)</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="466"/>
        <source>Threads</source>
        <translation>Threads</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="477"/>
        <source>Standalone (open replies in a side panel)</source>
        <translation>Standalone (open replies in a side panel)</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="478"/>
        <source>Inline (expand replies under the message)</source>
        <translation>Inline (expand replies under the message)</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="489"/>
        <source>Composer</source>
        <translation>Composer</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="495"/>
        <source>Send with %1</source>
        <translation>Send with %1</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="500"/>
        <source>Conversations</source>
        <translation>Conversations</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="511"/>
        <source>Show conversations active in the last</source>
        <translation>Show conversations active in the last</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="517"/>
        <source> days</source>
        <translation> days</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="524"/>
        <source>Conversations with no activity in this period are hidden
under an &quot;N more...&quot; row at the bottom of each section.</source>
        <translation>Conversations with no activity in this period are hidden
under an &quot;N more...&quot; row at the bottom of each section.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="532"/>
        <source>Show the Agents &amp;&amp; apps section</source>
        <translation>Show the Agents &amp;&amp; apps section</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="535"/>
        <source>Show only unread conversations</source>
        <translation>Show only unread conversations</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="538"/>
        <source>The conversation you are reading stays listed until you move on.
Starred conversations are always shown.</source>
        <translation>The conversation you are reading stays listed until you move on.
Starred conversations are always shown.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="559"/>
        <source>Save</source>
        <translation>Save</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="576"/>
        <source>Enable desktop notifications</source>
        <translation>Enable desktop notifications</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="585"/>
        <source>All new messages</source>
        <translation>All new messages</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="586"/>
        <source>Direct messages and mentions only</source>
        <translation>Direct messages and mentions only</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="596"/>
        <source>Notify me when a huddle starts</source>
        <translation>Notify me when a huddle starts</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="599"/>
        <source>Play a sound for notifications</source>
        <translation>Play a sound for notifications</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="608"/>
        <source>Sound:</source>
        <translation>Sound:</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="613"/>
        <source>Test</source>
        <translation>Test</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="628"/>
        <source>Sample notifications</source>
        <translation>Sample notifications</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="636"/>
        <source>New DM</source>
        <translation>New DM</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="637"/>
        <source>New channel message</source>
        <translation>New channel message</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="638"/>
        <source>New huddle</source>
        <translation>New huddle</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="641"/>
        <source>Test</source>
        <translation>Test</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="671"/>
        <source>Save</source>
        <translation>Save</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="691"/>
        <source>Cache</source>
        <translation>Cache</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="696"/>
        <source>Cache size:</source>
        <translation>Cache size:</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="706"/>
        <source>Conversations, user names, message history, and image thumbnails
stored locally to speed up startup.</source>
        <translation>Conversations, user names, message history, and image thumbnails
stored locally to speed up startup.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="715"/>
        <source>Limit cache to</source>
        <translation>Limit cache to</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="721"/>
        <source> MB</source>
        <translation> MB</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="728"/>
        <source>When the cache grows past this limit, the least recently
viewed images are deleted first.</source>
        <translation>When the cache grows past this limit, the least recently
viewed images are deleted first.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="747"/>
        <source>Clear cache</source>
        <translation>Clear cache</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="757"/>
        <source>State</source>
        <translation>State</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="762"/>
        <source>Sidebar visit history used to decide which conversations are shown.
Clear this to let the app re-analyse activity from scratch on next load.</source>
        <translation>Sidebar visit history used to decide which conversations are shown.
Clear this to let the app re-analyse activity from scratch on next load.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="772"/>
        <source>Clear state</source>
        <translation>Clear state</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="791"/>
        <source>Version</source>
        <translation>Version</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="798"/>
        <source>Version %1, built %2</source>
        <translation>Version %1, built %2</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="809"/>
        <source>Check for updates automatically</source>
        <translation>Check for updates automatically</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="817"/>
        <source>When off, msga never contacts the update server on its own — use the
button below to look for a new version.</source>
        <translation>When off, msga never contacts the update server on its own — use the
button below to look for a new version.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="826"/>
        <source>Check for updates</source>
        <translation>Check for updates</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="848"/>
        <source>Window</source>
        <translation>Window</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="858"/>
        <source>Minimize to tray</source>
        <translation>Minimize to tray</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="868"/>
        <source>When on, minimizing hides the window to the tray instead of the taskbar.
Click the tray icon to bring it back.</source>
        <translation>When on, minimizing hides the window to the tray instead of the taskbar.
Click the tray icon to bring it back.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="883"/>
        <source>Presence</source>
        <translation>Presence</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="893"/>
        <source>Show me as active while MSGA is running</source>
        <translation>Show me as active while MSGA is running</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="895"/>
        <source>Show me as active while I use MSGA (away after 30 minutes without input)</source>
        <translation>Show me as active while I use MSGA (away after 30 minutes without input)</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="897"/>
        <source>Leave my presence to the official Slack apps</source>
        <translation>Leave my presence to the official Slack apps</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="907"/>
        <source>Slack only shows you as active while a Slack app is connected. MSGA can hold that connection itself, so you no longer need the official app open to look online. The Hide button still makes you appear away. Works for workspaces added with a Slack session.</source>
        <translation>Slack only shows you as active while a Slack app is connected. MSGA can hold that connection itself, so you no longer need the official app open to look online. The Hide button still makes you appear away. Works for workspaces added with a Slack session.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="944"/>
        <source>Slack connection</source>
        <translation>Slack connection</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="948"/>
        <source>Choose how msga connects to Slack.</source>
        <translation>Choose how msga connects to Slack.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="960"/>
        <source>Slack session — no app keys, uses your own account's limits</source>
        <translation>Slack session — no app keys, uses your own account's limits</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="963"/>
        <source>Slack app keys — OAuth sign-in with live message push</source>
        <translation>Slack app keys — OAuth sign-in with live message push</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="969"/>
        <source>Restart msga to apply this change.</source>
        <translation>Restart msga to apply this change.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="982"/>
        <source>Add a workspace using your existing Slack session. New messages arrive by polling — there's no live push in this mode.</source>
        <translation>Add a workspace using your existing Slack session. New messages arrive by polling — there's no live push in this mode.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="991"/>
        <source>Import Slack session…</source>
        <translation>Import Slack session…</translation>
    </message>
    <message numerus="yes">
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1010"/>
        <source>You still have %n Slack workspace(s) on app keys. Convert them to session so no workspace uses Socket Mode.</source>
        <translation>
            <numerusform>You still have %n Slack workspace on app keys. Convert them to session so no workspace uses Socket Mode.</numerusform>
            <numerusform>You still have %n Slack workspaces on app keys. Convert them to session so no workspace uses Socket Mode.</numerusform>
        </translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1021"/>
        <source>Convert them to session</source>
        <translation>Convert them to session</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1042"/>
        <source>Run your own Slack app so you don't share connection keys with other devices and users. Leave a field empty to use the built-in default.</source>
        <translation>Run your own Slack app so you don't share connection keys with other devices and users. Leave a field empty to use the built-in default.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1051"/>
        <source>How to create your Slack app…</source>
        <translation>How to create your Slack app…</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1083"/>
        <source>Client ID</source>
        <translation>Client ID</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1083"/>
        <source>e.g. 1234567890.1234567890</source>
        <translation>e.g. 1234567890.1234567890</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1084"/>
        <source>Client secret</source>
        <translation>Client secret</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1084"/>
        <source>Paste your client secret</source>
        <translation>Paste your client secret</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1085"/>
        <source>App-level token</source>
        <translation>App-level token</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1085"/>
        <source>Paste your xapp- token</source>
        <translation>Paste your xapp- token</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1094"/>
        <source>Save and restart</source>
        <translation>Save and restart</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1128"/>
        <source>GIF picker</source>
        <translation>GIF picker</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1133"/>
        <source>Searching GIFs from the message box needs a GIPHY API key. Free keys allow 100 searches an hour, which is plenty for personal use.</source>
        <translation>Searching GIFs from the message box needs a GIPHY API key. Free keys allow 100 searches an hour, which is plenty for personal use.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1142"/>
        <source>Get a GIPHY API key…</source>
        <translation>Get a GIPHY API key…</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1157"/>
        <source>API key</source>
        <translation>API key</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1165"/>
        <source>Paste your GIPHY API key</source>
        <translation>Paste your GIPHY API key</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1166"/>
        <source>Using this build's key — paste one here to override it</source>
        <translation>Using this build's key — paste one here to override it</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1178"/>
        <source>Save</source>
        <translation>Save</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1184"/>
        <source>Key cleared.</source>
        <translation>Key cleared.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1184"/>
        <source>Key saved.</source>
        <translation>Key saved.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1195"/>
        <source>Memory</source>
        <translation>Memory</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1216"/>
        <source>RAM used: %1</source>
        <translation>RAM used: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1229"/>
        <source>License</source>
        <translation>License</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1234"/>
        <source>MSGA — Make Slack Great Again
Copyright © 2026 Vladimir Osipov

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version (GPL-3.0-or-later).</source>
        <translation>MSGA — Make Slack Great Again
Copyright © 2026 Vladimir Osipov

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version (GPL-3.0-or-later).</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1247"/>
        <source>View full license</source>
        <translation>View full license</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1259"/>
        <source>Contact</source>
        <translation>Contact</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1265"/>
        <source>Questions or feedback: %1</source>
        <translation>Questions or feedback: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1273"/>
        <source>Found a bug?</source>
        <translation>Found a bug?</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1278"/>
        <source>Report it on GitHub so it can be tracked and fixed.</source>
        <translation>Report it on GitHub so it can be tracked and fixed.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1284"/>
        <source>Report a bug</source>
        <translation>Report a bug</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1314"/>
        <source>AI provider</source>
        <translation>AI provider</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1319"/>
        <source>Connect an AI provider to enable assistant features.
API keys are stored on this computer and sent only to the provider you configure.</source>
        <translation>Connect an AI provider to enable assistant features.
API keys are stored on this computer and sent only to the provider you configure.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1335"/>
        <source>Add OpenAI-compatible server…</source>
        <translation>Add OpenAI-compatible server…</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1372"/>
        <source>Name</source>
        <translation>Name</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1373"/>
        <source>Company vLLM</source>
        <translation>Company vLLM</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1384"/>
        <source>Server URL</source>
        <translation>Server URL</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1394"/>
        <source>Works with vLLM, Ollama, LM Studio, LiteLLM, OpenRouter and other OpenAI-compatible servers.</source>
        <translation>Works with vLLM, Ollama, LM Studio, LiteLLM, OpenRouter and other OpenAI-compatible servers.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1403"/>
        <source>Unencrypted connection — the API key is sent in plain text.</source>
        <translation>Unencrypted connection — the API key is sent in plain text.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1417"/>
        <source>API key</source>
        <translation>API key</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1437"/>
        <source>Model</source>
        <translation>Model</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1438"/>
        <source>Model name</source>
        <translation>Model name</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1440"/>
        <source>Fetch models</source>
        <translation>Fetch models</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1463"/>
        <source>Test connection</source>
        <translation>Test connection</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1468"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1472"/>
        <source>Save</source>
        <translation>Save</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1493"/>
        <source>Your language</source>
        <translation>Your language</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1498"/>
        <source>AI features address you in this language.
It follows the app language until you pick one here.</source>
        <translation>AI features address you in this language.
It follows the app language until you pick one here.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1507"/>
        <source>Native language:</source>
        <translation>Native language:</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1603"/>
        <source>Connected (%1)</source>
        <translation>Connected (%1)</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1604"/>
        <source>Not connected</source>
        <translation>Not connected</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1617"/>
        <source>Connect</source>
        <translation>Connect</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1624"/>
        <source>Edit</source>
        <translation>Edit</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1632"/>
        <source>Disconnect</source>
        <translation>Disconnect</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1632"/>
        <source>Remove</source>
        <translation>Remove</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1686"/>
        <source>Add OpenAI-compatible server</source>
        <translation>Add OpenAI-compatible server</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1687"/>
        <source>Optional</source>
        <translation>Optional</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1688"/>
        <source>Leave empty if the server doesn't need one.</source>
        <translation>Leave empty if the server doesn't need one.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1693"/>
        <source>Connect %1</source>
        <translation>Connect %1</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1700"/>
        <source>Key saved (%1) — leave empty to keep it</source>
        <translation>Key saved (%1) — leave empty to keep it</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1704"/>
        <source>Paste your API key</source>
        <translation>Paste your API key</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1706"/>
        <source>Leave empty if the server doesn't need one.</source>
        <translation>Leave empty if the server doesn't need one.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1710"/>
        <source>Get an API key from %1…</source>
        <translation>Get an API key from %1…</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1757"/>
        <source>Enter the server URL first</source>
        <translation>Enter the server URL first</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1768"/>
        <source>Connecting…</source>
        <translation>Connecting…</translation>
    </message>
    <message numerus="yes">
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1779"/>
        <source>Reached the server — %n model(s) available</source>
        <translation>
            <numerusform>Reached the server — %n model available</numerusform>
            <numerusform>Reached the server — %n models available</numerusform>
        </translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1822"/>
        <source>Paste your API key</source>
        <translation>Paste your API key</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1827"/>
        <source>Enter the server URL (for example http://localhost:8000/v1)</source>
        <translation>Enter the server URL (for example http://localhost:8000/v1)</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="1831"/>
        <source>Enter a model name, or fetch the list from the server</source>
        <translation>Enter a model name, or fetch the list from the server</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2247"/>
        <source>No Slack workspace can provide a theme</source>
        <translation>No Slack workspace can provide a theme</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2252"/>
        <source>Could not read your Slack theme (%1)</source>
        <translation>Could not read your Slack theme (%1)</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2262"/>
        <source>Your Slack account has no custom theme</source>
        <translation>Your Slack account has no custom theme</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2267"/>
        <source>Slack theme applied</source>
        <translation>Slack theme applied</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2278"/>
        <source>Follows the system setting (currently dark)</source>
        <translation>Follows the system setting (currently dark)</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2279"/>
        <source>Follows the system setting (currently light)</source>
        <translation>Follows the system setting (currently light)</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2383"/>
        <source>No changes to save.</source>
        <translation>No changes to save.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2387"/>
        <source>Saved. Restarting…</source>
        <translation>Saved. Restarting…</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2435"/>
        <source>Last checked: %1</source>
        <translation>Last checked: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2443"/>
        <source>Update checks not available.</source>
        <translation>Update checks not available.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2448"/>
        <source>Checking for updates…</source>
        <translation>Checking for updates…</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2451"/>
        <source>Update downloaded — restart the app to apply.</source>
        <translation>Update downloaded — restart the app to apply.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2465"/>
        <source>Checking for updates…</source>
        <translation>Checking for updates…</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2469"/>
        <source>msga is up to date.</source>
        <translation>msga is up to date.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2473"/>
        <source>Version %1 available — downloading…</source>
        <translation>Version %1 available — downloading…</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2476"/>
        <source>Downloading update… %1%</source>
        <translation>Downloading update… %1%</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2480"/>
        <source>Update downloaded — restart the app to apply.</source>
        <translation>Update downloaded — restart the app to apply.</translation>
    </message>
    <message>
        <location filename="../src/ui/settings/settings_dialog.cpp" line="2485"/>
        <source>Check failed: %1</source>
        <translation>Check failed: %1</translation>
    </message>
</context>
<context>
    <name>StatusDialog</name>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="105"/>
        <source>Set a status</source>
        <translation>Set a status</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="150"/>
        <source>What's your status?</source>
        <translation>What's your status?</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="161"/>
        <source>In a meeting</source>
        <translation>In a meeting</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="162"/>
        <source>Commuting</source>
        <translation>Commuting</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="163"/>
        <source>Out sick</source>
        <translation>Out sick</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="164"/>
        <source>Vacationing</source>
        <translation>Vacationing</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="165"/>
        <source>Working remotely</source>
        <translation>Working remotely</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="168"/>
        <source>Don't clear</source>
        <translation>Don't clear</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="169"/>
        <source>30 minutes</source>
        <translation>30 minutes</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="170"/>
        <source>1 hour</source>
        <translation>1 hour</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="171"/>
        <source>4 hours</source>
        <translation>4 hours</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="172"/>
        <source>Today</source>
        <translation>Today</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="173"/>
        <source>This week</source>
        <translation>This week</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="179"/>
        <source>Suggestions</source>
        <translation>Suggestions</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="179"/>
        <source>For %1</source>
        <translation>For %1</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="203"/>
        <source>Clear after</source>
        <translation>Clear after</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="210"/>
        <source>Don't clear</source>
        <translation>Don't clear</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="211"/>
        <source>30 minutes</source>
        <translation>30 minutes</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="212"/>
        <source>1 hour</source>
        <translation>1 hour</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="213"/>
        <source>4 hours</source>
        <translation>4 hours</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="214"/>
        <source>Today</source>
        <translation>Today</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="215"/>
        <source>This week</source>
        <translation>This week</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="226"/>
        <source>Clear status</source>
        <translation>Clear status</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="231"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="../src/ui/status_dialog/status_dialog.cpp" line="232"/>
        <source>Save</source>
        <translation>Save</translation>
    </message>
</context>
<context>
    <name>SummarizeJob</name>
    <message>
        <location filename="../src/ui/summary_dialog/summarize_job.cpp" line="58"/>
        <source>Summarizing discussion…</source>
        <translation>Summarizing discussion…</translation>
    </message>
    <message>
        <location filename="../src/ui/summary_dialog/summarize_job.cpp" line="120"/>
        <source>Nothing to summarize — no text messages in the selected range.</source>
        <translation>Nothing to summarize — no text messages in the selected range.</translation>
    </message>
    <message>
        <location filename="../src/ui/summary_dialog/summarize_job.cpp" line="142"/>
        <source>Couldn't summarize: %1</source>
        <translation>Couldn't summarize: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/summary_dialog/summarize_job.cpp" line="183"/>
        <source>[shared a file]</source>
        <translation>[shared a file]</translation>
    </message>
    <message>
        <location filename="../src/ui/summary_dialog/summarize_job.cpp" line="184"/>
        <source>[shared a file: %1]</source>
        <translation>[shared a file: %1]</translation>
    </message>
</context>
<context>
    <name>SummaryDialog</name>
    <message>
        <location filename="../src/ui/summary_dialog/summary_dialog.cpp" line="53"/>
        <source>Discussion summary</source>
        <translation>Discussion summary</translation>
    </message>
    <message>
        <location filename="../src/ui/summary_dialog/summary_dialog.cpp" line="85"/>
        <source>Copy</source>
        <translation>Copy</translation>
    </message>
    <message>
        <location filename="../src/ui/summary_dialog/summary_dialog.cpp" line="88"/>
        <source>Copied</source>
        <translation>Copied</translation>
    </message>
    <message>
        <location filename="../src/ui/summary_dialog/summary_dialog.cpp" line="89"/>
        <source>Copy</source>
        <translation>Copy</translation>
    </message>
    <message>
        <location filename="../src/ui/summary_dialog/summary_dialog.cpp" line="96"/>
        <source>Open settings</source>
        <translation>Open settings</translation>
    </message>
</context>
<context>
    <name>ThreadExportJob</name>
    <message>
        <location filename="../src/ui/thread_panel/thread_export_job.cpp" line="52"/>
        <source>Downloading thread…</source>
        <translation>Downloading thread…</translation>
    </message>
    <message>
        <location filename="../src/ui/thread_panel/thread_export_job.cpp" line="118"/>
        <source>Thread in %1</source>
        <translation>Thread in %1</translation>
    </message>
    <message>
        <location filename="../src/ui/thread_panel/thread_export_job.cpp" line="119"/>
        <source>Messages: %1</source>
        <translation>Messages: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/thread_panel/thread_export_job.cpp" line="126"/>
        <source>(edited)</source>
        <translation>(edited)</translation>
    </message>
    <message>
        <location filename="../src/ui/thread_panel/thread_export_job.cpp" line="132"/>
        <source>[file: %1]</source>
        <translation>[file: %1]</translation>
    </message>
    <message>
        <location filename="../src/ui/thread_panel/thread_export_job.cpp" line="132"/>
        <source>untitled</source>
        <translation>untitled</translation>
    </message>
</context>
<context>
    <name>ThreadPanel</name>
    <message>
        <location filename="../src/ui/thread_panel/thread_panel.cpp" line="71"/>
        <source>Thread</source>
        <translation>Thread</translation>
    </message>
    <message>
        <location filename="../src/ui/thread_panel/thread_panel.cpp" line="231"/>
        <source>Reply in thread…</source>
        <translation>Reply in thread…</translation>
    </message>
    <message>
        <location filename="../src/ui/thread_panel/thread_panel.cpp" line="287"/>
        <source>Save thread</source>
        <translation>Save thread</translation>
    </message>
    <message>
        <location filename="../src/ui/thread_panel/thread_panel.cpp" line="297"/>
        <source>Download thread as text</source>
        <translation>Download thread as text</translation>
    </message>
</context>
<context>
    <name>ThreadsPage</name>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="179"/>
        <source>%1 files</source>
        <translation>%1 files</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="322"/>
        <source>New</source>
        <translation>New</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="354"/>
        <source>Show 1 more reply</source>
        <translation>Show 1 more reply</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="354"/>
        <source>Show %1 more replies</source>
        <translation>Show %1 more replies</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="370"/>
        <source>Reply in thread…</source>
        <translation>Reply in thread…</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="505"/>
        <source>%1 and %2 others</source>
        <translation>%1 and %2 others</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="508"/>
        <source>you</source>
        <translation>you</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="509"/>
        <source>%1 and you</source>
        <translation>%1 and you</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="547"/>
        <source>Reply in thread…</source>
        <translation>Reply in thread…</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="617"/>
        <source>Threads</source>
        <translation>Threads</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="640"/>
        <source>Show more threads</source>
        <translation>Show more threads</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="714"/>
        <source>Loading threads…</source>
        <translation>Loading threads…</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="744"/>
        <source>Threads you're following will appear here.</source>
        <translation>Threads you're following will appear here.</translation>
    </message>
    <message>
        <location filename="../src/ui/threads_page/threads_page.cpp" line="754"/>
        <source>Couldn't load threads. Try again later.</source>
        <translation>Couldn't load threads. Try again later.</translation>
    </message>
</context>
<context>
    <name>TitleBar</name>
    <message>
        <location filename="../src/ui/title_bar/title_bar.cpp" line="216"/>
        <source>Unpin window</source>
        <translation>Unpin window</translation>
    </message>
    <message>
        <location filename="../src/ui/title_bar/title_bar.cpp" line="216"/>
        <source>Pin window on top</source>
        <translation>Pin window on top</translation>
    </message>
</context>
<context>
    <name>TranscriptDialog</name>
    <message>
        <location filename="../src/ui/transcript_dialog/transcript_dialog.cpp" line="18"/>
        <source>Transcript (auto-generated)</source>
        <translation>Transcript (auto-generated)</translation>
    </message>
    <message>
        <location filename="../src/ui/transcript_dialog/transcript_dialog.cpp" line="25"/>
        <source>Loading…</source>
        <translation>Loading…</translation>
    </message>
    <message>
        <location filename="../src/ui/transcript_dialog/transcript_dialog.cpp" line="42"/>
        <source>Copy</source>
        <translation>Copy</translation>
    </message>
    <message>
        <location filename="../src/ui/transcript_dialog/transcript_dialog.cpp" line="46"/>
        <source>Copied</source>
        <translation>Copied</translation>
    </message>
    <message>
        <location filename="../src/ui/transcript_dialog/transcript_dialog.cpp" line="47"/>
        <source>Copy</source>
        <translation>Copy</translation>
    </message>
</context>
<context>
    <name>TypingIndicatorWidget</name>
    <message>
        <location filename="../src/ui/typing_indicator/typing_indicator.cpp" line="94"/>
        <source>&lt;b&gt;You&lt;/b&gt; are typing on another device…</source>
        <translation>&lt;b&gt;You&lt;/b&gt; are typing on another device…</translation>
    </message>
    <message>
        <location filename="../src/ui/typing_indicator/typing_indicator.cpp" line="102"/>
        <source>You</source>
        <translation>You</translation>
    </message>
    <message>
        <location filename="../src/ui/typing_indicator/typing_indicator.cpp" line="106"/>
        <source>%1 is typing…</source>
        <translation>%1 is typing…</translation>
    </message>
    <message>
        <location filename="../src/ui/typing_indicator/typing_indicator.cpp" line="106"/>
        <source>%1 are typing…</source>
        <translation>%1 are typing…</translation>
    </message>
</context>
<context>
    <name>UpdateBar</name>
    <message>
        <location filename="../src/ui/update_bar/update_bar.cpp" line="66"/>
        <source>A new version of msga has been downloaded. Restart to apply.</source>
        <translation>A new version of msga has been downloaded. Restart to apply.</translation>
    </message>
    <message>
        <location filename="../src/ui/update_bar/update_bar.cpp" line="67"/>
        <source>Restart now</source>
        <translation>Restart now</translation>
    </message>
    <message>
        <location filename="../src/ui/update_bar/update_bar.cpp" line="69"/>
        <source>A new version of msga is ready to install.</source>
        <translation>A new version of msga is ready to install.</translation>
    </message>
    <message>
        <location filename="../src/ui/update_bar/update_bar.cpp" line="70"/>
        <source>Open installer</source>
        <translation>Open installer</translation>
    </message>
</context>
<context>
    <name>UpdateChecker</name>
    <message>
        <location filename="../src/ui/update_checker/update_checker.cpp" line="93"/>
        <source>Automatic updates are not supported on this platform.</source>
        <translation>Automatic updates are not supported on this platform.</translation>
    </message>
    <message>
        <location filename="../src/ui/update_checker/update_checker.cpp" line="115"/>
        <source>Could not parse version manifest.</source>
        <translation>Could not parse version manifest.</translation>
    </message>
    <message>
        <location filename="../src/ui/update_checker/update_checker.cpp" line="135"/>
        <source>Cannot write update to %1</source>
        <translation>Cannot write update to %1</translation>
    </message>
    <message>
        <location filename="../src/ui/update_checker/update_checker.cpp" line="162"/>
        <source>Download failed: %1</source>
        <translation>Download failed: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/update_checker/update_checker.cpp" line="179"/>
        <source>Could not replace binary: %1</source>
        <translation>Could not replace binary: %1</translation>
    </message>
    <message>
        <location filename="../src/ui/update_checker/update_checker.cpp" line="195"/>
        <source>Could not move current binary — check file permissions on %1</source>
        <translation>Could not move current binary — check file permissions on %1</translation>
    </message>
    <message>
        <location filename="../src/ui/update_checker/update_checker.cpp" line="201"/>
        <source>Could not place new binary at %1</source>
        <translation>Could not place new binary at %1</translation>
    </message>
</context>
<context>
    <name>UserProfileCard</name>
    <message>
        <location filename="../src/ui/user_profile_card/user_profile_card.cpp" line="70"/>
        <source>Deactivated account</source>
        <translation>Deactivated account</translation>
    </message>
    <message>
        <location filename="../src/ui/user_profile_card/user_profile_card.cpp" line="72"/>
        <source>Workspace Owner</source>
        <translation>Workspace Owner</translation>
    </message>
    <message>
        <location filename="../src/ui/user_profile_card/user_profile_card.cpp" line="74"/>
        <source>Workspace Admin</source>
        <translation>Workspace Admin</translation>
    </message>
    <message>
        <location filename="../src/ui/user_profile_card/user_profile_card.cpp" line="76"/>
        <source>App</source>
        <translation>App</translation>
    </message>
    <message>
        <location filename="../src/ui/user_profile_card/user_profile_card.cpp" line="84"/>
        <source>%1 local time</source>
        <translation>%1 local time</translation>
    </message>
    <message>
        <location filename="../src/ui/user_profile_card/user_profile_card.cpp" line="123"/>
        <source>Message</source>
        <translation>Message</translation>
    </message>
    <message>
        <location filename="../src/ui/user_profile_card/user_profile_card.cpp" line="395"/>
        <source>Copied</source>
        <translation>Copied</translation>
    </message>
    <message>
        <location filename="../src/ui/user_profile_card/user_profile_card.cpp" line="432"/>
        <source>Message</source>
        <translation>Message</translation>
    </message>
</context>
<context>
    <name>WelcomeWidget</name>
    <message>
        <location filename="../src/ui/welcome_tips/welcome_widget.cpp" line="25"/>
        <source>Keyboard shortcuts</source>
        <translation>Keyboard shortcuts</translation>
    </message>
</context>
<context>
    <name>WorkspaceSwitcher</name>
    <message>
        <location filename="../src/ui/workspace_switcher/workspace_switcher.cpp" line="422"/>
        <source>Add workspace</source>
        <translation>Add workspace</translation>
    </message>
    <message>
        <location filename="../src/ui/workspace_switcher/workspace_switcher.cpp" line="425"/>
        <source>Settings</source>
        <translation>Settings</translation>
    </message>
</context>
<context>
    <name>relativeTime</name>
    <message>
        <location filename="../src/util/relative_time.cpp" line="10"/>
        <source>just now</source>
        <translation>just now</translation>
    </message>
    <message numerus="yes">
        <location filename="../src/util/relative_time.cpp" line="13"/>
        <source>%n minute ago</source>
        <translation>
            <numerusform>%n minute ago</numerusform>
            <numerusform>%n minute ago</numerusform>
        </translation>
    </message>
    <message numerus="yes">
        <location filename="../src/util/relative_time.cpp" line="17"/>
        <source>%n hour ago</source>
        <translation>
            <numerusform>%n hour ago</numerusform>
            <numerusform>%n hour ago</numerusform>
        </translation>
    </message>
    <message numerus="yes">
        <location filename="../src/util/relative_time.cpp" line="21"/>
        <source>%n day ago</source>
        <translation>
            <numerusform>%n day ago</numerusform>
            <numerusform>%n day ago</numerusform>
        </translation>
    </message>
    <message numerus="yes">
        <location filename="../src/util/relative_time.cpp" line="25"/>
        <source>%n month ago</source>
        <translation>
            <numerusform>%n month ago</numerusform>
            <numerusform>%n month ago</numerusform>
        </translation>
    </message>
    <message numerus="yes">
        <location filename="../src/util/relative_time.cpp" line="28"/>
        <source>%n year ago</source>
        <translation>
            <numerusform>%n year ago</numerusform>
            <numerusform>%n year ago</numerusform>
        </translation>
    </message>
</context>
<context>
    <name>Sound</name>
    <message>
        <location filename="../src/util/sound_player.cpp" line="53"/>
        <source>msga chime</source>
        <translation>msga chime</translation>
    </message>
</context>
<context>
    <name>domain</name>
    <message>
        <location filename="../src/backend/domain.h" line="930"/>
        <source>Huddle happened</source>
        <translation>Huddle happened</translation>
    </message>
</context>
</TS>
