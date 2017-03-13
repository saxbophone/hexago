/*
 * This should compile, provided the target system has the appropriate headers
 */
#import <ScreenSaver/ScreenSaver.h>

#include <SFML/Window.hpp>

#include "hexago/HexagoScreenSaver.hpp"


@interface HexagoScreenSaverView : ScreenSaverView {
    /*
     * Pointers to C++ objects are used here because Objective-C++ cannot
     * handle C++ objects with user-provided constructors nor those with
     * virtual methods, as statically allocated variables.
     */
    // store SFML window C++ object pointer as instance variable
    sf::RenderWindow* sfml_window;
    // same goes for our HexagoScreenSaver C++ object
    hexago::HexagoScreenSaver* screensaver;
} @end
