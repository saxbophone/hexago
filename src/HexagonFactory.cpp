#include <random>

#include "HexagonFactory.hpp"
#include "HexagonFactoryConfig.hpp"
#include "Hexagon.hpp"
#include "colour.hpp"


namespace hexago {

    // constructor
    HexagonFactory::HexagonFactory(HexagonFactoryConfig& config) :
        /*
         * all of the properties are set via an initialiser list, reading from
         * config object.
         *
         * std::random_device has two parens for a reason:
         * once for constructing the type
         * second for calling it, as that's what will give us random samples
         */
        random_number_engine(std::mt19937(std::random_device()())),
        x_spawn_range(config.spawn_lower_bound.x, config.spawn_upper_bound.x),
        y_spawn_range(config.spawn_lower_bound.y, config.spawn_upper_bound.y),
        start_size_range(
            config.start_size_range.min, config.start_size_range.max
        ),
        decay_speed_range(
            config.decay_speed_range.min, config.decay_speed_range.max
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
