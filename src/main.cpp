#include <string>
#include <sstream>

#include <cstdio>

#include <SFML/Window.hpp>

#include "main.hpp"
#include "HexagoScreenSaver.hpp"
#include "ArgumentParser.hpp"


// Version numbers are passed as preprocessor definitions by CMake
const hexago::version_t hexago::VERSION = {
    HEXAGO_VERSION_MAJOR,
    HEXAGO_VERSION_MINOR,
    HEXAGO_VERSION_PATCH,
    HEXAGO_VERSION_BUILD,
    HEXAGO_VERSION_STRING,
};

// program copyright notice
const char* copyright = "Copyright (c) 2017 Joshua Saxby. All rights reserved.";

int main(int argc, char* argv[]) {
    // build window title / console 'greet' message
    std::ostringstream window_title_stream;
    window_title_stream << "Hexago v" << hexago::VERSION.string;
    window_title_stream << " (build " << hexago::VERSION.build << ")";
    std::string window_title = window_title_stream.str();
    // print Hexago version and copyright notice, on separate lines
    printf("%s\n%s\n", window_title.c_str(), copyright);
    // get supported fullscreen video modes
    std::vector<sf::VideoMode> video_modes = sf::VideoMode::getFullscreenModes();
    // window settings
    sf::ContextSettings settings;
    // set anti-aliasing
    settings.antialiasingLevel = 8;
    // get first (best) fullscreen videomode and init window with it
    sf::RenderWindow window(
        video_modes[0], window_title, sf::Style::Fullscreen, settings
    );
    // hide the mouse cursor
    window.setMouseCursorVisible(false);

    /*
     * get screen saver config from command-line arguments, then instantiate a
     * HexagoScreenSaver object, handing it our window and config
     */
    hexago::HexagoScreenSaver app(window, hexago::parse_arguments(argc, argv));

    // loop while window remains open
    while(window.isOpen()) {
        // call the update method to update internal state and draw the frame
        app.update();
    }
    return 0;
}
