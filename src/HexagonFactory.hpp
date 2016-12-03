#ifndef SAXBOPHONE_HEXAGO_HEXAGON_FACTORY_HPP
#define SAXBOPHONE_HEXAGO_HEXAGON_FACTORY_HPP

#include <SFML/System/Vector2.hpp>

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
                hexagon_size_t start_size_min,
                hexagon_size_t start_size_max,
                hexagon_decay_t decay_speed_min,
                hexagon_decay_t decay_speed_max
            );
            // returns a new Hexagon instance from the factory
            Hexagon next();
        private:
            // the lower bound of the area which Hexagons may be spawned in
            sf::Vector2f spawn_lower_bound;
            // the upper bound of the area which Hexagons may be spawned in
            sf::Vector2f spawn_upper_bound;
            // the minimum starting size for any new Hexagon
            hexagon_size_t start_size_min;
            // the maximum starting size for any new Hexagon
            hexagon_size_t start_size_max;
            // the minimum decay speed for any new Hexagon
            hexagon_decay_t decay_speed_min;
            // the maximum decay speed for any new Hexagon
            hexagon_decay_t decay_speed_max;
    };

}

#endif // include guard
