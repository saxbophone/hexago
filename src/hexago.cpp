#include <cstdint>
#include <cstdio>

#include <SFML/Graphics.hpp>

#include "hexago.hpp"

// Version numbers are passed as preprocessor definitions by CMake
const hexago::version_t hexago::VERSION = {
    HEXAGO_VERSION_MAJOR,
    HEXAGO_VERSION_MINOR,
    HEXAGO_VERSION_PATCH,
    HEXAGO_VERSION_STRING,
};

int main() {
    printf("Hexago v%s\n", hexago::VERSION.string);
    sf::Window App(sf::VideoMode(800, 600), "myproject");

    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                App.close();
            }
        }
        App.display();
    }
    return 0;
}
