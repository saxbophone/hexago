/*
 * This should compile, provided the target system has the appropriate headers
 */
// check that ARC is enabled - we need it othwerwise our code is invalid
#if ! __has_feature(objc_arc)
#error "ARC is not enabled or supported. This file will not compile without it."
#endif

#include <SFML/Window.hpp>

#import "mac_osx.hh"

#include "hexago/HexagoScreenSaver.hpp"


@implementation HexagoScreenSaverView

- (id)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview {
    self = [super initWithFrame:frame isPreview:isPreview];
    if(self) {
        /*
         * TODO: This should use framerate from our config object instead, or
         * even possibly be removed...
         */
        [self setAnimationTimeInterval:1/30.0];
    }
    return self;
}

- (void)startAnimation {
    [super startAnimation];
    /*
     * initialise our screensaver from a native window handle (in this case,
     * we can use self as ScreenSaverView inherits from NSView, which is a
     * window handle - it's basically a void pointer as far as C++ and
     * Objective-C++ are concerned)
     */
    screensaver = new hexago::HexagoScreenSaver((__bridge_retained sf::WindowHandle)self);
}

- (void)stopAnimation {
    [super stopAnimation];
}

// this method has to be implemented, but we don't do our drawing here
- (void)drawRect:(NSRect)rect {
    [super drawRect:rect];
}

- (void)animateOneFrame {
    // call screensaver.update() to render one frame
    screensaver->update();
}

- (BOOL)hasConfigureSheet {
    // There is no configuration dialog (yet)
    return NO;
}

- (NSWindow*)configureSheet {
    // TODO: Implement configuration dialog
    return nil;
}

- (void)dealloc {
    // hook into dealloc message so we relinquish resources (our C++ object!)
    delete screensaver;
}

@end
