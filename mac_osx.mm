/*
 * XXX: This code was written on Linux and HAS NOT BEEN TESTED AT ALL (yet)
 */
#include <SFML/Window.hpp>

#import "mac_osx.hh"

#include "hexago/HexagoScreenSaver.hpp"


@implementation HexagoScreenSaverView

static NSString * const MyModuleName = @"com.saxbophone.HexagoScreenSaver";

- (id)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview {
    self = [super initWithFrame:frame isPreview:isPreview];
    if (self) {
        /*
         * TODO: This should use framerate from our config object instead, or
         * even possibly be removed...
         */
        [self setAnimationTimeInterval:1/30.0];
        /*
         * initialise an SFML window from a native window handle (in this case,
         * we can use self as ScreenSaverView inherits from NSView, which SFML
         * will accept as a window handle)
         */
        sfml_window = sf::RenderWindow(self); // TODO: include sf::ContextSettings
        // intialise screensaver app with window instance
        screensaver = hexago::HexagoScreenSaver(sfml_window);
    }
    return self;
}

- (void)startAnimation {
    [super startAnimation];
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
    screensaver.update();
}

- (BOOL)hasConfigureSheet {
    // There is no configuration dialog (yet)
    return NO;
}

- (NSWindow *)configureSheet {
    // TODO: Implement configuration dialog
    return nil;
}

@end
