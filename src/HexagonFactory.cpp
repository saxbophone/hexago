#include <random>

#include "HexagonFactory.hpp"
#include "Hexagon.hpp"


namespace hexago {

    // constructor
    HexagonFactory::HexagonFactory(
        sf::Vector2f spawn_lower_bound,
        sf::Vector2f spawn_upper_bound,
        ParameterRange<hexagon_size_t> start_size_range,
        ParameterRange<hexagon_decay_t> decay_speed_range,
        ParameterRange<double> d_colour_channel_range,
        ParameterRange<double> e_colour_channel_range,
        ParameterRange<double> f_colour_channel_range,
        ParameterRange<double> alpha_colour_channel_range
    ) :
        /*
         * all of the properties are set via an initialiser list
         *
         * std::random_device has two parens for a reason:
         * once for constructing the type
         * second for calling it, as that's what will give us random samples
         */
        random_number_engine(std::mt19937(std::random_device()())),
        x_spawn_range(spawn_lower_bound.x, spawn_upper_bound.x),
        y_spawn_range(spawn_lower_bound.y, spawn_upper_bound.y),
        start_size_range(start_size_range.min, start_size_range.max),
        decay_speed_range(decay_speed_range.min, decay_speed_range.max),
        d_colour_channel_range(
            d_colour_channel_range.min, d_colour_channel_range.max
        ),
        e_colour_channel_range(
            e_colour_channel_range.min, e_colour_channel_range.max
        ),
        f_colour_channel_range(
            f_colour_channel_range.min, f_colour_channel_range.max
        ),
        alpha_colour_channel_range(
            alpha_colour_channel_range.min, alpha_colour_channel_range.max
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
            sf::Color(
                d_colour_channel_range(this->random_number_engine),
                e_colour_channel_range(this->random_number_engine),
                f_colour_channel_range(this->random_number_engine),
                alpha_colour_channel_range(this->random_number_engine)
            )
        );
    }

}
