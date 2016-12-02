#ifndef SAXBOPHONE_HEXAGO_HEXAGON_HPP
#define SAXBOPHONE_HEXAGO_HEXAGON_HPP

#include <cstdint>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>


namespace hexago {

    typedef int32_t hexagon_size_t;
    typedef uint16_t hexagon_decay_t;
    typedef float seconds_alive_t;

    class Hexagon {
        public:
            // constructor
            Hexagon(
                sf::Vector2f centre,
                hexagon_size_t start_size,
                hexagon_decay_t decay_rate
            );
            // returns a SFML shape which can be used to render this hexagon
            sf::CircleShape shape();
            // returns true if this hexagon has finished shrinking
            bool is_dead();
        private:
            // the location of the hexagon on screen
            sf::Vector2f centre;
            // the start size of the hexagon (radius in pixels)
            hexagon_size_t start_size;
            // how many pixels smaller the hexagon should get in 1 second
            hexagon_decay_t decay_rate;
            // counter referencing the time that the hexagon was 'born'
            sf::Clock birth_time;
            /*
             * returns fractional seconds count of how long this hexagon has
             * been 'alive' for
             */
            seconds_alive_t time_alive();
            /*
             * returns current size of the hexagon in pixels, based on birth
             * time, the time right now and the decay rate
             */
            hexagon_size_t current_size();
    };

}

#endif // include guard
