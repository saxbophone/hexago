/*
 * XXX: This code was written on Linux and HAS NOT BEEN TESTED AT ALL (yet)
 */
#import <ScreenSaver/ScreenSaver.h>

#include <SFML/Window.hpp>

#include "hexago/HexagoScreenSaver.hpp"


@interface HexagoScreenSaverView : ScreenSaverView {
    // store SFML window C++ object as instance variable
    sf::RenderWindow sfml_window;
    // same goes for our HexagoScreenSaver C++ object
    hexago::HexagoScreenSaver screensaver;
} @end
