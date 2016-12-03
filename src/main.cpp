#include <string>

#include <cstdio>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "main.hpp"
#include "Hexagon.hpp"
#include "HexagonFactory.hpp"


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
    sf::RenderWindow window(
        video_modes[0], window_title, sf::Style::Default, settings
    );
    // enable vertical sync so we don't have to worry about framerate sync
    window.setVerticalSyncEnabled(true);
    // get window dimensions
    sf::Vector2f window_size = sf::Vector2f(window.getSize());

    // instantiate a HexagonFactory object
    hexago::HexagonFactory factory(
        sf::Vector2f(0.0f, 0.0f), // spawn lower bounds
        window_size, // spawn upper bounds
        window_size.y / 12.0f, // minimum starting size
        window_size.y / 6.0f, // maximum starting size
        window_size.y / 32.0f, // minimum decay speed
        (hexago::hexagon_decay_t)(window_size.y / 16.0f) // maximum decay speed
    );

    const size_t HEXAGON_COUNT = 1024;
    // this is the array where we store Hexagons.
    hexago::Hexagon hexagons[HEXAGON_COUNT];
    // instantiate all the Hexagons in the array
    for(size_t i = 0; i < HEXAGON_COUNT; i++) {
        // use the factory to get random hexagons, yay!
        hexagons[i] = factory.next();
    }

    while(window.isOpen()) {
        sf::Event Event;
        while(window.pollEvent(Event)) {
            if(Event.type == sf::Event::Closed) {
                window.close();
                // skip frame
                continue;
            }
        }
        // clear the window with black color
        window.clear(sf::Color::Black);
        // loop over all the hexagons in the array
        for(size_t i = 0; i < HEXAGON_COUNT; i++) {
            // check if the hexagon needs 're-birthing'
            if(hexagons[i].is_dead()) {
                hexagons[i] = factory.next();
            }
            // render the hexagon to screen
            window.draw(hexagons[i].shape());
        }
        // draw out the rendered frame
        window.display();
    }
    return 0;
}
