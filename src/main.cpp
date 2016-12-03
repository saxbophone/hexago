#include <string>

#include <cstdint>
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
    const std::string window_title = (
        (std::string)"Hexago v" + hexago::VERSION.string
    );
    printf("%s\n", window_title.c_str());
    sf::RenderWindow window(sf::VideoMode(800, 600), window_title);
    // enable vertical sync so we don't have to worry about framerate sync
    window.setVerticalSyncEnabled(true);

    // construct a Hexagon object
    hexago::Hexagon hexagon(sf::Vector2f(400, 300), 300, 60);

    while(window.isOpen()) {
        sf::Event Event;
        while(window.pollEvent(Event)) {
            if(Event.type == sf::Event::Closed) {
                window.close();
            }
        }
        // check if the hexagon needs 're-birthing'
        if(hexagon.is_dead()) {
            hexagon = hexago::Hexagon(sf::Vector2f(400, 300), 300, 60);
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
