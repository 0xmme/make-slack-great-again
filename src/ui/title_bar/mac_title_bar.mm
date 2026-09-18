// SPDX-License-Identifier: GPL-3.0-or-later
#include "mac_title_bar.h"
#include "ui/theme.h"

#include <QGuiApplication>
#include <QWidget>

#import <AppKit/AppKit.h>

void configureMacTitleBar(QWidget *widget) {
    // Widget tests also run on macOS using the offscreen platform plugin.
    if (QGuiApplication::platformName() != "cocoa")
        return;
    NSView   *view   = reinterpret_cast<NSView *>(widget->winId());
    NSWindow *window = view.window;
    if (!window)
        return;

    // Qt < 6.9 has no expanded-client-area hint. Setting the native style also
    // restores it if Qt recreates the NSWindow after its flags change.
    if (!(window.styleMask & NSWindowStyleMaskFullSizeContentView))
        window.styleMask |= NSWindowStyleMaskFullSizeContentView;
    window.titleVisibility            = NSWindowTitleHidden;
    window.titlebarAppearsTransparent = YES;
    // An empty native toolbar gives the traffic lights the standard, centered
    // placement of a unified macOS header. AppKit owns the buttons and behavior.
    if (!window.toolbar) {
        NSToolbar *toolbar              = [[NSToolbar alloc] initWithIdentifier:@"msga.titlebar"];
        toolbar.allowsUserCustomization = NO;
        window.toolbar                  = toolbar;
        [toolbar release];
    }
    if (@available(macOS 11.0, *)) {
        window.toolbarStyle           = NSWindowToolbarStyleUnified;
        window.titlebarSeparatorStyle = NSTitlebarSeparatorStyleNone;
    }
    const bool dark = Th::c().surface.content.lightnessF() < 0.5;
    window.appearance =
        [NSAppearance appearanceNamed:dark ? NSAppearanceNameDarkAqua : NSAppearanceNameAqua];
}
