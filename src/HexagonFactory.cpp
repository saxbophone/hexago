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
        hexagon_size_t start_size_min,
        hexagon_size_t start_size_max,
        hexagon_decay_t decay_speed_min,
        hexagon_decay_t decay_speed_max,
        uint8_t red_colour_channel_minimum,
        uint8_t red_colour_channel_maximum,
        uint8_t green_colour_channel_minimum,
        uint8_t green_colour_channel_maximum,
        uint8_t blue_colour_channel_minimum,
        uint8_t blue_colour_channel_maximum,
        uint8_t alpha_colour_channel_minimum,
        uint8_t alpha_colour_channel_maximum
        // almost all of the properties are set via an initialiser list
    ) : x_spawn_range(spawn_lower_bound.x, spawn_upper_bound.x),
        y_spawn_range(spawn_lower_bound.y, spawn_upper_bound.y),
        start_size_range(start_size_min, start_size_max),
        decay_speed_range(decay_speed_min, decay_speed_max),
        red_colour_channel_range(
            red_colour_channel_minimum, red_colour_channel_maximum
        ),
        green_colour_channel_range(
            green_colour_channel_minimum, green_colour_channel_maximum
        ),
        blue_colour_channel_range(
            blue_colour_channel_minimum, blue_colour_channel_maximum
        ),
        alpha_colour_channel_range(
            alpha_colour_channel_minimum, alpha_colour_channel_maximum
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
