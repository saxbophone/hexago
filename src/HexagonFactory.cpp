#include <random>

#include "HexagonFactory.hpp"
#include "Hexagon.hpp"


namespace hexago {

    // default constructor, does nothing. Provided as convenience.
    HexagonFactory::HexagonFactory() {}

    // constructor
    HexagonFactory::HexagonFactory(
        sf::Vector2f spawn_lower_bound,
        sf::Vector2f spawn_upper_bound,
        ParameterRange<hexagon_size_t> start_size_range,
        ParameterRange<hexagon_decay_t> decay_speed_range,
        ParameterRange<uint8_t> red_colour_channel_range,
        ParameterRange<uint8_t> green_colour_channel_range,
        ParameterRange<uint8_t> blue_colour_channel_range,
        ParameterRange<uint8_t> alpha_colour_channel_range
        // almost all of the properties are set via an initialiser list
    ) : x_spawn_range(spawn_lower_bound.x, spawn_upper_bound.x),
        y_spawn_range(spawn_lower_bound.y, spawn_upper_bound.y),
        start_size_range(start_size_range.min, start_size_range.max),
        decay_speed_range(decay_speed_range.min, decay_speed_range.max),
        red_colour_channel_range(
            red_colour_channel_range.min, red_colour_channel_range.max
        ),
        green_colour_channel_range(
            green_colour_channel_range.min, green_colour_channel_range.max
        ),
        blue_colour_channel_range(
            blue_colour_channel_range.min, blue_colour_channel_range.max
        ),
        alpha_colour_channel_range(
            alpha_colour_channel_range.min, alpha_colour_channel_range.max
        ) {
        // seed the random number engine
        std::random_device random_device;
        this->random_number_engine = std::mt19937(random_device());
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
            // a random opaque colour
            sf::Color(
                red_colour_channel_range(this->random_number_engine),
                green_colour_channel_range(this->random_number_engine),
                blue_colour_channel_range(this->random_number_engine),
                alpha_colour_channel_range(this->random_number_engine)
            )
        );
    }

}
