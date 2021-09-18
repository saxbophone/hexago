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
     *
     * BUG: There is a memory leak at this point.
     * Unbeknown to me, it turns out that startAnimation() may be called
     * again after stopAnimation() for the same instance of a ScreenSaverView
     * subclass (this happens for example in the System Preferences screen
     * after finishing changing the settings of a ScreenSaver).
     * I've tried to remediate the issue by delete-ing the object in
     * stopAnimation(), but the trouble is that this crashes the entire thing.
     * It is possible to delete C++ objects in Objective-C++ in this way, so
     * there must be something wrong with my HexagoScreenSaver class which
     * makes instances of it un-delete-able.
     */
    screensaver = new hexago::HexagoScreenSaver(
        /*
         * this is a bridged cast, a feature of ARC in objective-C and
         * essentially means that, from here-on we're the owner of this
         * pointer's memory and are responsible for it.
         * However, given that `self` is the class instance itself, I'm not
         * sure that we need to worry about releasing it with free() or
         * CFRelease() at the end.
         */
        (__bridge_retained sf::WindowHandle)self
    );
    // render the first frame (this prevents a brief flash of white background)
    screensaver->update();
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
    // There IS a Configure Sheet
    return YES;
}

- (NSWindow*)configureSheet {
    // load our Configure Sheet
    if (!configSheet) {
        if (![NSBundle loadNibNamed:@"ConfigureSheet" owner:self]) {
            NSLog( @"Failed to load configure sheet." );
            NSBeep();
        }
    }
    return configSheet;
}

- (void)dealloc {
    // hook into dealloc message so we relinquish resources (our C++ object!)
    delete screensaver;
}

/* here begins additional Cocoa event-handling stuff for the Configure Sheet */

// closes the Configure Sheet
- (void)closeConfigSheet {
    [[NSApplication sharedApplication] endSheet:configSheet];
}

// event-handler for the "Cancel" button of the Configure Sheet
- (IBAction)configureCancelClick:(id)sender {
    [self closeConfigSheet];
}

// event-handler for the "OK" button of the Configure Sheet
- (IBAction)configureOkClick:(id)sender {
    // TODO: save the settings configured in the Configure Sheet!
    [self closeConfigSheet];
}

/* here ends Cocoa event-handling stuff */

@end
