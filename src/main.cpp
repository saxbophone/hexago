#include <string>

#include <cstdio>

#include <SFML/Window.hpp>

#include "main.hpp"
#include "HexagoScreenSaver.hpp"


// Version numbers are passed as preprocessor definitions by CMake
const hexago::version_t hexago::VERSION = {
    HEXAGO_VERSION_MAJOR,
    HEXAGO_VERSION_MINOR,
    HEXAGO_VERSION_PATCH,
    HEXAGO_VERSION_STRING,
};

int main() {
    // build window title / console 'greet' message
    const std::string window_title = (
        (std::string)"Hexago v" + hexago::VERSION.string
    );
    printf("%s\n", window_title.c_str());

    /* Now we set up the window instance */
    // get supported fullscreen video modes
    std::vector<sf::VideoMode> video_modes = sf::VideoMode::getFullscreenModes();
    // set anti-aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    printf("Starting Screen Saver\n");
    // get first (best) fullscreen videomode and init window with it
    sf::RenderWindow window(
        video_modes[0], window_title, sf::Style::None, settings
    );
    // hide the mouse cursor
    window.setMouseCursorVisible(false);
    // enable vertical sync so we don't have to worry about framerate sync
    window.setVerticalSyncEnabled(true);

    // now we instantiate a HexagoScreenSaver object, handing it our window
    hexago::HexagoScreenSaver app(window);

    // loop while window remains open
    while(window.isOpen()) {
        // call the update method to update internal state and draw the frame
        app.update();
    }
    printf("Exit.\n");
    return 0;
}
