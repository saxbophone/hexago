#include <random>

#include "HexagonFactory.hpp"
#include "Hexagon.hpp"


namespace hexago {

    // constructor
    HexagonFactory::HexagonFactory(
        sf::Vector2f spawn_lower_bound,
        sf::Vector2f spawn_upper_bound,
        hexagon_size_t start_size_min,
        hexagon_size_t start_size_max,
        hexagon_decay_t decay_speed_min,
        hexagon_decay_t decay_speed_max
        // all the properties are set via an initialiser list
    ) : spawn_lower_bound(spawn_lower_bound),
        spawn_upper_bound(spawn_upper_bound),
        start_size_min(start_size_min),
        start_size_max(start_size_max),
        decay_speed_min(decay_speed_min),
        decay_speed_max(decay_speed_max) {}

    // returns a new Hexagon instance from the factory
    Hexagon HexagonFactory::next() {
        // get ranges for random numbers
        std::uniform_real_distribution<float> x_spawn_range(
            this->spawn_lower_bound.x, this->spawn_upper_bound.x
        );
        std::uniform_real_distribution<float> y_spawn_range(
            this->spawn_lower_bound.y, this->spawn_upper_bound.y
        );
        std::uniform_int_distribution<hexagon_size_t> start_size_range(
            this->start_size_min, this->start_size_max
        );
        std::uniform_int_distribution<hexagon_size_t> decay_speed_range(
            this->decay_speed_min, this->decay_speed_max
        );
        // get the default random number generator
        std::default_random_engine generator;
        // return a random Hexagon based on these random ranges
        return Hexagon(
            sf::Vector2f(x_spawn_range(generator), y_spawn_range(generator)),
            start_size_range(generator), decay_speed_range(generator),
            // TODO: Make colour random too
            sf::Color::White
        );
    }

}
