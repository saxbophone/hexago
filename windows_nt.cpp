// C++ stdlib
#include <iostream>
#include <string>
#include <sstream>
// C stdlib
#include <cassert>
#include <cstdio>
#include <cstdlib>
// C++ third-party
#include <SFML/Window.hpp>
// C third-party
#include <windows.h>
// C++ first-party
#include "hexago/hexago.hpp"
#include "hexago/HexagoScreenSaver.hpp"
#include "hexago/HexagoScreenSaverConfig.hpp"
#include "hexago/HexagonFactoryConfig.hpp"
#include "hexago/ParameterRange.hpp"
#include "hexago/argument_parser.hpp"


int main(int argc, const char* argv[]) {
    assert(argc == 3);
    // XXX: Assuming we get the window handle as 3rd argument
    HWND window_handle = (HWND)atoi(argv[2]);
    // hide console window
    // HWND console_handle = GetConsoleWindow(); 
    // ShowWindow(console_handle, SW_HIDE);
    // window settings
    sf::ContextSettings settings;
    // set anti-aliasing
    settings.antialiasingLevel = 8;
    // hand over the window handle and settings to SFML
    sf::RenderWindow window(window_handle, settings);
    // hide the mouse cursor
    window.setMouseCursorVisible(false);
    // instantiate the screensaver app with this window instance
    hexago::HexagoScreenSaver screensaver(window);
    // loop while window remains open and window handle remains valid
    while(window.isOpen() && IsWindow(window_handle)) {
        // call the update method to update internal state and draw the frame
        screensaver.update();
    }
    return 0;
}
