#ifndef SAXBOPHONE_HEXAGO_HEXAGON_FACTORY_HPP
#define SAXBOPHONE_HEXAGO_HEXAGON_FACTORY_HPP

#include <random>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "HexagonFactoryConfig.hpp"
#include "Hexagon.hpp"


namespace hexago {

    /*
     * A class which produces new random Hexagon objects when requested.
     * The properties of the Hexagon objects produced are controlled by
     * the config object passed to the constructor. Window bounds and the
     * window dimension used to scale hexagon sizes should also be passed.
     */
    class HexagonFactory {
        public:
            // constructor
            HexagonFactory(
                HexagonFactoryConfig& config,
                sf::Vector2u window_size,
                double scaling_dimension
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
            std::uniform_real_distribution<hexagon_size_t> start_size_range;
            // the range within which decay speeds of new Hexagons may fall
            std::uniform_real_distribution<hexagon_decay_t> decay_speed_range;
            // the colour model to use for hexagon colours
            hexago::colour_model_t colour_model;
            // the range of acceptable values for each colour channel
            // channel d
            std::uniform_real_distribution<colour_channel_t>
                d_colour_channel_range;
            // channel e
            std::uniform_real_distribution<colour_channel_t>
                e_colour_channel_range;
            // channel f
            std::uniform_real_distribution<colour_channel_t>
                f_colour_channel_range;
            // alpha channel
            std::uniform_real_distribution<colour_channel_t>
                alpha_colour_channel_range;

            // gets a new random colour for a Hexagon
            sf::Color colour();
    };

}

#endif // include guard