#include <string>

#include <cstdio>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "main.hpp"
#include "hexagon.hpp"

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
    // get supported fullscreen video modes
    std::vector<sf::VideoMode> video_modes = sf::VideoMode::getFullscreenModes();
    // set anti-aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    // get first (best) fullscreen videomode and init window with it
    sf::RenderWindow window(video_modes[0], window_title, sf::Style::Default, settings);
    // enable vertical sync so we don't have to worry about framerate sync
    window.setVerticalSyncEnabled(true);
    // get window dimensions
    sf::Vector2f window_size = sf::Vector2f(window.getSize());

    // construct a Hexagon object
    hexago::Hexagon hexagon(window_size / 2.0f, 300, 60);

    while(window.isOpen()) {
        sf::Event Event;
        while(window.pollEvent(Event)) {
            if(Event.type == sf::Event::Closed) {
                window.close();
            }
        }
        // check if the hexagon needs 're-birthing'
        if(hexagon.is_dead()) {
            hexagon = hexago::Hexagon(window_size / 2.0f, 300, 60);
        }
        // clear the window with black color
        window.clear(sf::Color::Black);
        // create a hexagon shape to render from the Hexagon object
        sf::CircleShape hexagon_shape = hexagon.shape();
        // set render colour to white
        hexagon_shape.setFillColor(sf::Color::White);
        // draw the shape on the window
        window.draw(hexagon_shape);
        // draw out the rendered frame
        window.display();
    }
    return 0;
}
