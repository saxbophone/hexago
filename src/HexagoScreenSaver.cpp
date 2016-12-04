#include <cmath>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
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
        // get the calculated number of hexagons required
        this->hexagon_count = this->required_number_of_hexagons();
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

    float HexagoScreenSaver::HEXAGON_NUMBER_TUNING_CONSTANT = 30.0f;

    size_t HexagoScreenSaver::required_number_of_hexagons() const {
        // get the screen area first
        sf::Vector2u screen_size = this->window.getSize();
        size_t screen_area = screen_size.x * screen_size.y;
        // now get the average hexagon radius
        float average_hexagon_radius = (
            ((float)screen_size.y * this->config.minimum_hexagon_size)
            +
            ((float)screen_size.y * this->config.maximum_hexagon_size)
        ) / 2.0f;
        /*
         * the area of a regular hexagon may be found with the side length or 
         * radius as follows, where r is the radius length of the hexagon:
         *
         * a = {[3 * sqrt(3)] * (r ^ 2)} / 2
         */
        float average_hexagon_area = (
            ((3.0f * sqrt(3.0f)) * pow(average_hexagon_radius, 2.0f)) / 2.0f
        );
        /*
         * The number of hexagons needed to attain a given amount of screen
         * cover may be calculated with the following formula:
         *
         * (screen_area / average_hexagon_area) * cover_amount * TUNING_CONSTANT
         */
        return (size_t)(
            ((float)screen_area / average_hexagon_area)
            * this->config.minimum_screen_cover
            * HEXAGON_NUMBER_TUNING_CONSTANT
        );
    }

}
