#include <deque>

#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "HexagoScreenSaver.hpp"
#include "ParameterRange.hpp"
#include "HexagonFactory.hpp"


namespace hexago {

    // simple constructor
    HexagoScreenSaver::HexagoScreenSaver(
        sf::RenderWindow& window
    ) : HexagoScreenSaver(window, DEFAULT_CONFIG) {}

    // customisation constructor
    HexagoScreenSaver::HexagoScreenSaver(
        sf::RenderWindow& window, screen_saver_config_t config
    )
    :
    window(window),
    window_size(window.getSize()),
    config(config),
    hexagon_factory(
        sf::Vector2f(0.0f, 0.0f), // spawn lower bounds
        sf::Vector2f(window_size), // spawn upper bounds
        ParameterRange<hexagon_size_t>(
            window_size.y * this->config.minimum_hexagon_size,
            window_size.y * this->config.maximum_hexagon_size
        ),
        ParameterRange<hexagon_decay_t>(
            window_size.y * this->config.minimum_hexagon_decay_speed,
            window_size.y * this->config.maximum_hexagon_decay_speed
        ),
        ParameterRange<uint8_t>(
            this->config.red_colour_channel_minimum,
            this->config.red_colour_channel_maximum
        ),
        ParameterRange<uint8_t>(
            this->config.green_colour_channel_minimum,
            this->config.green_colour_channel_maximum
        ),
        ParameterRange<uint8_t>(
            this->config.blue_colour_channel_minimum,
            this->config.blue_colour_channel_maximum
        ),
        ParameterRange<uint8_t>(
            this->config.alpha_colour_channel_minimum,
            this->config.alpha_colour_channel_maximum
        )
    ),
    hexagon_count(required_number_of_hexagons()) {
        // populate the array with Hexagon instances from the factory
        for(size_t i = 0; i < this->hexagon_count; i++) {
            this->hexagons.push_back(this->hexagon_factory.next());
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
                if(this->config.spawn_mode == SPAWN_MODE_DEFAULT) {
                    /*
                     * default is to just respawn Hexagons in-place, as far as
                     * z-indexing is concerned. This series of calls:
                     * 1. Removes the existing Hexagon object
                     * 2. Inserts a new one from the factory in its place
                     */
                    this->hexagons.insert(
                        this->hexagons.erase(
                            this->hexagons.begin() + i
                        ),
                        this->hexagon_factory.next()
                    );
                } else {
                    /*
                     * for both of the other spawn modes, we remove the dead
                     * Hexagon from its current position first
                     */
                    this->hexagons.erase(this->hexagons.begin() + i);
                    // now, we put it at top or bottom depending on spawn mode
                    if(this->config.spawn_mode == SPAWN_MODE_BOTTOM) {
                        // add its replacement at the start of the deque
                        this->hexagons.push_front(this->hexagon_factory.next());
                    } else if(this->config.spawn_mode == SPAWN_MODE_TOP) {
                        // add its replacement at the end of the deque
                        this->hexagons.push_back(this->hexagon_factory.next());
                    }
                }
            }
            // render the hexagon to screen
            this->window.draw(this->hexagons[i].shape());
        }
        // draw out the rendered frame
        this->window.display();
    }
    /*
     * a static constant member which stores the default configuration
     * for the Screen Saver, as screen_saver_config_t struct
     */
    const screen_saver_config_t HexagoScreenSaver::DEFAULT_CONFIG = {
        // these are the default config settings
        // they are written as fractions like this to aid human readability
        (1.0f / 12.0f), // minimum_hexagon_size
        (1.0f / 6.0f), // maximum_hexagon_size
        (1.0f / 32.0f), // minimum_hexagon_decay_speed
        (1.0f / 16.0f), // maximum_hexagon_decay_speed
        0, // red colour channel minimum
        255, // red colour channel maximum
        0, // green colour channel minimum
        255, // green colour channel maximum
        0, // blue colour channel minimum
        255, // blue colour channel maximum
        255, // alpha colour channel minimum
        255, // alpha colour channel maximum
        (100.0f / 100.0f), // minimum_screen_cover
        SPAWN_MODE_DEFAULT, // spawn_mode
        BG_MODE_BLACK, // background_mode
    };

    /*
     * a tuning constant for the mechanics which calculates the number
     * of hexagons which need to be drawn
     */
    const float HexagoScreenSaver::HEXAGON_NUMBER_TUNING_CONSTANT = 30.0f;

    size_t HexagoScreenSaver::required_number_of_hexagons() const {
        // get the screen area first
        size_t screen_area = this->window_size.x * this->window_size.y;
        // now get the average hexagon radius
        float average_hexagon_radius = (
            ((float)this->window_size.y * this->config.minimum_hexagon_size)
            +
            ((float)this->window_size.y * this->config.maximum_hexagon_size)
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
