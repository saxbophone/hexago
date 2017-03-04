#ifndef SAXBOPHONE_HEXAGO_HEXAGON_HPP
#define SAXBOPHONE_HEXAGO_HEXAGON_HPP

#include <cstdint>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>


namespace hexago {

    typedef double hexagon_size_t;
    typedef double hexagon_decay_t;
    typedef double seconds_alive_t;

    /*
     * A class used to represent a Hexagon shape that currently exists on the
     * screen. Hexagons have a starting size, shrink rate, colour and position.
     * All of these attributes are set at instantiation and are used to render
     * an image of the Hexagon at any current point in time.
     */
    class Hexagon {
        public:
            // constructor
            Hexagon(
                sf::Vector2f centre,
                hexagon_size_t start_size,
                hexagon_decay_t decay_rate,
                sf::Color colour
            );
            // returns a SFML shape which can be used to render this hexagon
            sf::CircleShape shape() const;
            // returns true if this hexagon has finished shrinking
            bool is_dead() const;
        private:
            /*
             * returns fractional seconds count of how long this hexagon has
             * been 'alive' for
             */
            seconds_alive_t time_alive() const;
            /*
             * returns current size of the hexagon in pixels, based on birth
             * time, the time right now and the decay rate
             */
            hexagon_size_t current_size() const;

            // the location of the hexagon on screen
            sf::Vector2f centre;
            // the start size of the hexagon (radius in pixels)
            hexagon_size_t start_size;
            // how many pixels smaller the hexagon should get in 1 second
            hexagon_decay_t decay_rate;
            // counter referencing the time that the hexagon was 'born'
            sf::Clock birth_time;
            // the colour of this hexagon
            sf::Color colour;
    };

}

#endif // include guard
