#include <algorithm>
#include <deque>

#include <cmath>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "HexagoScreenSaver.hpp"
#include "HexagoScreenSaverConfig.hpp"
#include "ParameterRange.hpp"
#include "Hexagon.hpp"


namespace hexago {

    // simple constructor
    HexagoScreenSaver::HexagoScreenSaver(sf::RenderWindow& window)
      : HexagoScreenSaver(window, default_config())
      {}

    // customisation constructor
    HexagoScreenSaver::HexagoScreenSaver(
        sf::RenderWindow& window, HexagoScreenSaverConfig config
    )
      : window(window)
      , config(config)
      , hexagon_factory(config, this->window_size(), this->scaling_dimension())
      , hexagon_count(required_number_of_hexagons())
      {
        // set window framerate to what is given in config
        window.setFramerateLimit(config.framerate);
        // populate the array with Hexagon instances from the factory
        for(size_t i = 0; i < this->hexagon_count; i++) {
            this->hexagons.push_back(this->hexagon_factory.next());
        }
    }

    // this method returns the size of the window we're bound to
    sf::Vector2u HexagoScreenSaver::window_size() const {
        return this->window.getSize();
    }

    // returns the size of the window dimension to use for scaling 
    double HexagoScreenSaver::scaling_dimension() const {
        sf::Vector2u window_size = this->window_size();
        // scaling dimension is smallest of window x and y
        return (double)std::min(window_size.x, window_size.y);
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
                if(this->config.spawn_mode == SPAWN_MODE_SAME) {
                    // respawn Hexagons in-place, at the same z-index
                    this->hexagons[i] = this->hexagon_factory.next();
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

    // retrieves the default config
    HexagoScreenSaverConfig HexagoScreenSaver::default_config() {
        return HexagoScreenSaverConfig(
            // start_size_range
            ParameterRange<hexagon_size_t>(12.0, 6.0),
            // decay_speed_range
            ParameterRange<hexagon_decay_t>(32.0, 16.0),
            COLOUR_MODEL_RGB, // colour_model
            // d_colour_channel_range
            ParameterRange<colour_channel_t>(0.0, 255.0),
            // e_colour_channel_range
            ParameterRange<colour_channel_t>(0.0, 255.0),
            // f_colour_channel_range
            ParameterRange<colour_channel_t>(0.0, 255.0),
            // alpha_colour_channel_range
            ParameterRange<colour_channel_t>(100.0, 100.0),
            30, // framerate
            (100.0 / 100.0), // minimum_screen_cover
            SPAWN_MODE_BOTTOM, // spawn_mode
            BG_COLOUR_BLACK // background_mode
        );
    }

    size_t HexagoScreenSaver::required_number_of_hexagons() const {
        // get the screen area first
        sf::Vector2u window_size = this->window_size();
        size_t screen_area = window_size.x * window_size.y;
        // now get the average hexagon radius
        double scaling_dimension = this->scaling_dimension();
        double average_hexagon_radius = (
            (scaling_dimension / this->config.start_size_range.min)
            +
            (scaling_dimension / this->config.start_size_range.max)
        ) / 2.0;
        /*
         * the area of a regular hexagon may be found with the side length or 
         * radius as follows, where r is the radius length of the hexagon:
         *
         * a = {[3 * sqrt(3)] * (r ^ 2)} / 2
         */
        double average_hexagon_area = (
            ((3.0 * sqrt(3.0)) * pow(average_hexagon_radius, 2.0)) / 2.0
        );
        /*
         * The number of hexagons needed to attain a given amount of screen
         * cover may be calculated with the following formula:
         *
         * (screen_area / average_hexagon_area) * cover_amount * TUNING_CONSTANT
         */
        return (size_t)(
            ((double)screen_area / average_hexagon_area)
            * this->config.minimum_screen_cover
            * HEXAGON_NUMBER_TUNING_CONSTANT
        );
    }

    /*
     * a tuning constant for the mechanics which calculates the number
     * of hexagons which need to be drawn
     */
    const double HexagoScreenSaver::HEXAGON_NUMBER_TUNING_CONSTANT = 30.0;

}
