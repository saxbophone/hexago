#include <string>
#include <vector>

#include <cstdio>
#include <cstdlib>

#include <SFML/Window.hpp>

#include <windows.h>

#include "hexago/hexago.hpp"
#include "hexago/HexagoScreenSaver.hpp"


static int run_preview(HWND window_handle, sf::ContextSettings settings) {
    // hand over the window handle and settings to SFML
    sf::RenderWindow window(window_handle, settings);
    // instantiate the screensaver app with this window instance
    hexago::HexagoScreenSaver screensaver(window);
    // loop while window remains open and window handle remains valid
    while(window.isOpen() && IsWindow(window_handle)) {
        // call the update method to update internal state and draw the frame
        screensaver.update();
    }
    return 0;
}


static int run_screensaver(sf::ContextSettings settings) {
    // get supported fullscreen video modes
    std::vector<sf::VideoMode> video_modes = sf::VideoMode::getFullscreenModes();
    // get first (best) fullscreen videomode and init window with it
    sf::RenderWindow window(
        video_modes[0], "Hexago", sf::Style::Fullscreen, settings
    );
    // hide the mouse cursor
    window.setMouseCursorVisible(false);
    // instantiate the screensaver app with this window instance
    hexago::HexagoScreenSaver screensaver(window);
    // loop while window remains open
    while(window.isOpen()) {
        // call the update method to update internal state and draw the frame
        screensaver.update();
    }
    return 0;
}


int main(int argc, char* argv[]) {
    // SFML window settings for later use
    sf::ContextSettings settings;
    // set anti-aliasing
    settings.antialiasingLevel = 8;
    // check command-line arguments
    if(argc < 2) {
        /*
         * there wasn't at least one argument, which means config mode was
         * requested - we don't support this (yet)
         */
        return 0;
    }
    // carry on and interrogate arguments
    std::string option = argv[1]; // get second argument
    if(option == "/s") {
        // wahoo! regular screensaver mode :)
        return run_screensaver(settings);
    } else if(option == "/p") {
        // this is preview mode, so we need to check the third argument
        if(argc < 3) { // check for not enough arguments
            fprintf(stderr, "Window handle required for preview mode\n");
            return 1;
        }
        // convert decimal string to window handle
        HWND window_handle = (HWND)atoi(argv[2]);
        // run preview mode with this window handle
        return run_preview(window_handle, settings);
    } else if(option == "/c") {
        // again, this is config mode (which we don't yet support)
        return 0;
    }
    return 0;
}
