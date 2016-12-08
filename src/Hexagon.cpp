#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "Hexagon.hpp"


namespace hexago {

    // default constructor, does nothing. Provided as convenience.
    Hexagon::Hexagon() {}

    // constructor
    Hexagon::Hexagon(
        sf::Vector2f centre,
        hexagon_size_t start_size,
        hexagon_decay_t decay_rate,
        sf::Color colour
        // all the properties are set via an initialiser list
    ) : centre(centre),
        start_size(start_size),
        decay_rate(decay_rate),
        colour(colour) {}

    // returns a SFML shape which can be used to render this hexagon
    sf::CircleShape Hexagon::shape() const {
        // grab the current size right now as it's used a few times
        hexagon_size_t current_size = this->current_size();
        /*
         * construct a CircleShape object with a radius of this Hexagon's size
         * and 6 sides (a hexagon)
         */
        sf::CircleShape shape(current_size, 6);
        /*
         * set the origin to the centre of the shape, as we want it to remain
         * anchored to the centre, not the top-left.
         * the centre is always the radius of the shape
         */
        shape.setOrigin(current_size, current_size);
        // now set the shape's position to that of this Hexagon object's centre
        shape.setPosition(this->centre);
        // finally, set the fill colour of this shape before returning it
        shape.setFillColor(this->colour);
        return shape;
    }

    bool Hexagon::is_dead() const {
        /*
         * TODO: Return true/false on whether this hexagon is finished, based
         * on birth time, current time, start size and decay time
         */
        return (this->current_size() <= 0);
    }

    /*
     * returns fractional seconds count of how long this hexagon has
     * been 'alive' for
     */
    seconds_alive_t Hexagon::time_alive() const {
        // get the time counted so far by our internal clock, in seconds
        return this->birth_time.getElapsedTime().asSeconds();
    }

    /*
     * returns current size of the hexagon in pixels, based on birth
     * time, the time right now and the decay rate
     */
    hexagon_size_t Hexagon::current_size() const {
        return (hexagon_size_t)(
            (seconds_alive_t)this->start_size - (
                (seconds_alive_t)this->decay_rate * this->time_alive()
            )
        );
    }

}
