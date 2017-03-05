#include <algorithm>
#include <random>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include <colrcv-0/models/rgb.h>
#include <colrcv-0/models/hsv.h>
#include <colrcv-0/models/lab.h>

#include "HexagonFactory.hpp"
#include "HexagonFactoryConfig.hpp"
#include "Hexagon.hpp"


namespace hexago {

    // constructor
    HexagonFactory::HexagonFactory(
        HexagonFactoryConfig& config, sf::Vector2u window_size
    ) :
        /*
         * all of the properties are set via an initialiser list, reading from
         * config object. additionally, the window size needs to be known so
         * that the spawn bounds can be configured and sizes relative to y size.
         *
         * std::random_device has two parens for a reason:
         * once for constructing the type
         * second for calling it, as that's what will give us random samples
         */
        random_number_engine(std::mt19937(std::random_device()())),
        x_spawn_range(0.0f, (float)window_size.x),
        y_spawn_range(0.0f, (float)window_size.y),
        colour_model(config.colour_model),
        d_colour_channel_range(
            config.d_colour_channel_range.min, config.d_colour_channel_range.max
        ),
        e_colour_channel_range(
            config.e_colour_channel_range.min, config.e_colour_channel_range.max
        ),
        f_colour_channel_range(
            config.f_colour_channel_range.min, config.f_colour_channel_range.max
        ),
        alpha_colour_channel_range(
            config.alpha_colour_channel_range.min,
            config.alpha_colour_channel_range.max
        ) {
            // window axis to use is the smallest one
            float window_axis = (float)std::min(window_size.x, window_size.y);
            this->start_size_range = std::uniform_real_distribution<hexagon_size_t>(
                window_size.y / config.start_size_range.min,
                window_size.y / config.start_size_range.max
            );
            this->decay_speed_range = std::uniform_real_distribution<hexagon_decay_t>(
                window_size.y / config.decay_speed_range.min,
                window_size.y / config.decay_speed_range.max
            );
        }

    // returns a randomly-generated Hexagon instance from the factory
    Hexagon HexagonFactory::next() {
        return Hexagon(
            // random starting position
            sf::Vector2f(
                x_spawn_range(this->random_number_engine),
                y_spawn_range(this->random_number_engine)
            ),
            // random starting size
            start_size_range(this->random_number_engine),
            // random decay speed
            decay_speed_range(this->random_number_engine),
            // use a new random colour
            this->colour()
        );
    }

    // gets a new random colour for a Hexagon, based on the chosen colour model
    sf::Color HexagonFactory::colour() {
        /*
         * set the colour differently depending on what model is being used
         * libcolrcv is used to achieve these conversions (if needed)
         */
        // colrcv rgb colour to be used later
        colrcv_rgb_t rgb;
        switch(this->colour_model) {
            case hexago::COLOUR_MODEL_RGB: {                
                // just store channels in rgb struct
                rgb.r = d_colour_channel_range(this->random_number_engine);
                rgb.g = e_colour_channel_range(this->random_number_engine);
                rgb.b = f_colour_channel_range(this->random_number_engine);
                break;
            }
            case hexago::COLOUR_MODEL_HSV: {                
                // create a new hsv colour
                colrcv_hsv_t hsv = {
                    d_colour_channel_range(this->random_number_engine),
                    e_colour_channel_range(this->random_number_engine),
                    f_colour_channel_range(this->random_number_engine),
                };
                // convert to rgb
                colrcv_hsv_to_rgb(hsv, &rgb);
                break;
            }
            case hexago::COLOUR_MODEL_LAB: {                
                // create a new lab colour
                colrcv_lab_t lab = {
                    d_colour_channel_range(this->random_number_engine),
                    e_colour_channel_range(this->random_number_engine),
                    f_colour_channel_range(this->random_number_engine),
                };
                // convert to rgb
                colrcv_lab_to_rgb(lab, &rgb);
                break;
            }
        }
        // convert colrcv rgb colour to an sf::Color instance and attach alpha
        return sf::Color(
            rgb.r,
            rgb.g,
            rgb.b,
            // alpha is given as range from 0-100 so turn this into 0-255
            alpha_colour_channel_range(this->random_number_engine) / 100.0 * 255
        );
    }

}
