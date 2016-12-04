#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "HexagoScreenSaver.hpp"
#include "HexagonFactory.hpp"


namespace hexago {

    // simple constructor
    HexagoScreenSaver::HexagoScreenSaver(
        sf::RenderWindow& window
    ) : HexagoScreenSaver(
            window,
            // these are the default config settings
            // they are written as fractions like this to aid human readability
            {
                (1.0f / 12.0f), // minimum_hexagon_size
                (1.0f / 6.0f), // maximum_hexagon_size
                (1.0f / 32.0f), // minimum_hexagon_decay_speed
                (1.0f / 16.0f), // maximum_hexagon_decay_speed
                (100.0f / 100.0f), // minimum_screen_cover
                SPAWN_MODE_DEFAULT, // spawn_mode
                BG_MODE_BLACK, // background_mode
            }
        ) {}

    // customisation constructor
    HexagoScreenSaver::HexagoScreenSaver(
        sf::RenderWindow& window, screen_saver_config_t config
    ) : window(window), config(config) {
        // get window dimensions
        sf::Vector2f window_size = sf::Vector2f(this->window.getSize());
        // instantiate the HexagonFactory with the config settings we've got
        this->hexagon_factory = HexagonFactory(
            sf::Vector2f(0.0f, 0.0f), // spawn lower bounds
            window_size, // spawn upper bounds
            window_size.y * this->config.minimum_hexagon_size,
            window_size.y * this->config.maximum_hexagon_size,
            window_size.y * this->config.minimum_hexagon_decay_speed,
            window_size.y * this->config.maximum_hexagon_decay_speed
        );
        // TODO: Rewrite to actually calculate the count based on screen size
        this->hexagon_count = 1024;
        // initialise the hexagons vector to this many elements
        this->hexagons = std::vector<Hexagon>(this->hexagon_count);
        // populate the array with Hexagon instances from the factory
        for(size_t i = 0; i < this->hexagon_count; i++) {
            this->hexagons[i] = this->hexagon_factory.next();
        }
    }

    // updates internal state and renders the hexagons to window
    void HexagoScreenSaver::update() {
        sf::Event event;
        while(this->window.pollEvent(event)) {
            switch(event.type) {
                /*
                 * any of the following event types in this series of case
                 * fall-throughs warrant a program exit.
                 */
                case sf::Event::Closed:
                case sf::Event::LostFocus:
                case sf::Event::KeyPressed:
                case sf::Event::KeyReleased:
                case sf::Event::MouseWheelScrolled:
                case sf::Event::MouseButtonPressed:
                case sf::Event::MouseButtonReleased:
                case sf::Event::MouseMoved:
                case sf::Event::MouseEntered:
                case sf::Event::MouseLeft:
                case sf::Event::TouchBegan:
                case sf::Event::TouchMoved:
                case sf::Event::TouchEnded:
                    this->window.close();
                    continue;
                default:
                    // do nothing;
                    break;
            }
        }
        // clear the window with black color
        this->window.clear(sf::Color::Black);
        // loop over all the hexagons in the array
        for(size_t i = 0; i < this->hexagon_count; i++) {
            // check if the hexagon needs 're-birthing'
            if(this->hexagons[i].is_dead()) {
                this->hexagons[i] = this->hexagon_factory.next();
            }
            // render the hexagon to screen
            this->window.draw(this->hexagons[i].shape());
        }
        // draw out the rendered frame
        this->window.display();
    }

}
