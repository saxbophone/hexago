/*
 * This should compile, provided the target system has the appropriate headers
 */
#import <ScreenSaver/ScreenSaver.h>

#include "hexago/HexagoScreenSaver.hpp"


@interface HexagoScreenSaverView : ScreenSaverView {
    /*
     * A pointer to the screensaver C++ object is used here because
     * Objective-C++ cannot handle C++ objects with user-provided constructors
     * nor those with virtual methods, as statically allocated variables.
     */
    hexago::HexagoScreenSaver* screensaver;
    // Configure Sheet stuff
    IBOutlet id configSheet;
    IBOutlet id drawFilledShapesOption;
    IBOutlet id drawOutlinedShapesOption;
    IBOutlet id drawBothOption;
} @end
