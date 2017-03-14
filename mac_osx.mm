/*
 * This should compile, provided the target system has the appropriate headers
 */
#include <SFML/Window.hpp>

#import "mac_osx.hh"

#include "hexago/HexagoScreenSaver.hpp"


@implementation HexagoScreenSaverView

static const NSString* MyModuleName = @"com.saxbophone.HexagoScreenSaver";

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
         * will accept as a window handle - it's basically a void pointer as
         * far as C++ is concerned)
         */
        /*
         * TODO: Check this cast is necessary - it may not be on OSX
         * (both types are void pointers as far as I'm aware)
         */
        sfml_window = new sf::RenderWindow((sf::WindowHandle)self);
        // TODO: include sf::ContextSettings in sf::RenderWindow constructor
        // intialise screensaver app with window instance
        screensaver = new hexago::HexagoScreenSaver(*sfml_window);
    }
    return self;
}

-(void)dealloc {
    // hook into dealloc message so we relinquish resources (our C++ objects!)
    delete sfml_window;
    delete screensaver;
    [super dealloc];
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
    screensaver->update();
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
