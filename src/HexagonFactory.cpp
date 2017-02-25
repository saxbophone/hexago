#include <random>

#include "HexagonFactory.hpp"
#include "HexagonFactoryConfig.hpp"
#include "Hexagon.hpp"
#include "colour.hpp"


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
        start_size_range(
            window_size.y * config.start_size_range.min,
            window_size.y * config.start_size_range.max
        ),
        decay_speed_range(
            window_size.y * config.decay_speed_range.min,
            window_size.y * config.decay_speed_range.max
        ),
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
        ) {}

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
            // a random opaque colour
            colour_from_lab_a({
                d_colour_channel_range(this->random_number_engine),
                e_colour_channel_range(this->random_number_engine),
                f_colour_channel_range(this->random_number_engine),
                alpha_colour_channel_range(this->random_number_engine),
            })
        );
    }

}
