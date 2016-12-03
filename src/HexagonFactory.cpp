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
        // almost all of the properties are set via an initialiser list
    ) : x_spawn_range(spawn_lower_bound.x, spawn_upper_bound.x),
        y_spawn_range(spawn_lower_bound.y, spawn_upper_bound.y),
        start_size_range(start_size_min, start_size_max),
        decay_speed_range(decay_speed_min, decay_speed_max) {
        // seed the random number engine
        std::random_device random_device;
        this->random_number_engine = std::default_random_engine(
            random_device()
        );
    }

    // returns a randomly-generated Hexagon instance from the factory
    Hexagon HexagonFactory::next() {
        return Hexagon(
            sf::Vector2f(
                x_spawn_range(this->random_number_engine),
                y_spawn_range(this->random_number_engine)
            ),
            start_size_range(this->random_number_engine),
            decay_speed_range(this->random_number_engine),
            // TODO: Make colour random too
            sf::Color::White
        );
    }

}
