/*
 * This is the Mac OSX version of the screensaver, written as a plugin
 * (as required by the OSX screensaver framework)
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
     * initialise an SFML window from a native window handle (in this case,
     * we can use self as ScreenSaverView inherits from NSView, which SFML
     * will accept as a window handle - it's basically a void pointer as
     * far as C++ and Objective-C++ are concerned)
     */
    // TODO: include sf::ContextSettings in sf::RenderWindow constructor
    sfml_window = new sf::RenderWindow((__bridge_retained sf::WindowHandle)self);
    // intialise screensaver app with window instance
    screensaver = new hexago::HexagoScreenSaver(*sfml_window);
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
    // hook into dealloc message so we relinquish resources (our C++ objects!)
    delete screensaver;
    delete sfml_window;
}

@end
