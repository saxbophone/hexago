#ifndef SAXBOPHONE_HEXAGO_HEXAGON_FACTORY_HPP
#define SAXBOPHONE_HEXAGO_HEXAGON_FACTORY_HPP

#include <random>

#include <cstdint>

#include <SFML/System/Vector2.hpp>

#include "ParameterRange.hpp"
#include "Hexagon.hpp"


namespace hexago {

    /*
     * A class which produces new random Hexagon objects when requested.
     * The properties of the Hexagon objects produced are controlled by
     * parameters set at the HexagonFactory's instantiation.
     */
    class HexagonFactory {
        public:
            // constructor
            HexagonFactory(
                sf::Vector2f spawn_lower_bound,
                sf::Vector2f spawn_upper_bound,
                ParameterRange<hexagon_size_t> start_size_range,
                ParameterRange<hexagon_decay_t> decay_speed_range,
                ParameterRange<uint8_t> red_colour_channel_range,
                ParameterRange<uint8_t> green_colour_channel_range,
                ParameterRange<uint8_t> blue_colour_channel_range,
                ParameterRange<uint8_t> alpha_colour_channel_range
            );
            // returns a randomly-generated Hexagon instance from the factory
            Hexagon next();
        private:
            // the random number engine we'll be using
            std::mt19937 random_number_engine;
            // the x co-ordinate range within which Hexagons may be spawned
            std::uniform_real_distribution<float> x_spawn_range;
            // the y co-ordinate range within which Hexagons may be spawned
            std::uniform_real_distribution<float> y_spawn_range;
            // the range within which start sizes of new Hexagons may fall
            std::uniform_int_distribution<hexagon_size_t> start_size_range;
            // the range within which decay speeds of new Hexagons may fall
            std::uniform_int_distribution<hexagon_size_t> decay_speed_range;
            // the range of acceptable values for each RGB channel
            // red channel
            std::uniform_int_distribution<sf::Uint8> red_colour_channel_range;
            // green channel
            std::uniform_int_distribution<sf::Uint8> green_colour_channel_range;
            // blue channel
            std::uniform_int_distribution<sf::Uint8> blue_colour_channel_range;
            // alpha channel
            std::uniform_int_distribution<sf::Uint8> alpha_colour_channel_range;
    };

}

#endif // include guard
