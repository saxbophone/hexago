#include <cmath>
#include <cstdint>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "hexagon.hpp"
#include "types.hpp"


namespace hexago {

    // constructor
    Hexagon::Hexagon(
        sf::Vector2f centre,
        hexagon_size_t start_size,
        hexagon_decay_t decay_rate
        // all the properties are set via an initialiser list
    ) : centre(centre), start_size(start_size), decay_rate(decay_rate) {}

    // returns a SFML shape which can be used to render this hexagon
    sf::CircleShape Hexagon::shape() {
        /*
         * construct a CircleShape object with a radius of this Hexagon's size
         * and 6 sides (a hexagon)
         */
        sf::CircleShape shape(this->current_size(), 6);
        // set the shape's position to that of this Hexagon object
        shape.setPosition(this->centre);
        return shape;
    }

    bool Hexagon::is_dead() {
        /*
         * TODO: Return true/false on whether this hexagon is finished, based
         * on birth time, current time, start size and decay time
         */
        return (bool)(this->current_size() <= 0);
    }

    /*
     * returns fractional seconds count of how long this hexagon has
     * been 'alive' for
     */
    seconds_alive_t Hexagon::time_alive() {
        // get the time counted so far by our internal clock, in seconds
        return this->birth_time.getElapsedTime().asSeconds();
    }

    /*
     * returns current size of the hexagon in pixels, based on birth
     * time, the time right now and the decay rate
     */
    hexagon_size_t Hexagon::current_size() {
        return (hexagon_size_t)(
            (seconds_alive_t)this->start_size - (
                (seconds_alive_t)this->decay_rate * this->time_alive()
            )
        );
    }

}
