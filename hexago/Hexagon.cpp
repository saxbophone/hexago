#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "Hexagon.hpp"


namespace hexago {

    // constructor
    Hexagon::Hexagon(
        sf::Vector2u window_size,
        sf::Vector2f centre,
        hexagon_size_t start_size,
        hexagon_decay_t decay_rate,
        sf::Color colour
        // all the properties are set via an initialiser list
    )
      : window_size(window_size)
      , centre(centre)
      , start_size(start_size)
      , decay_rate(decay_rate)
      , colour(colour)
      {}

    // returns a SFML shape which can be used to render this hexagon
    std::vector<sf::CircleShape> Hexagon::shapes() const {
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
        // set the shape fill colour --this never changes for all shapes
        shape.setFillColor(this->colour);
        /*
         * vector to store all shapes for this Hexagon
         * --we may need multiple shapes if the Hexagon overlaps any of the
         * screen edges, as we want to make a tileable image
         */
        std::vector<sf::CircleShape> shapes(1);
        // each Hexagon always has at least one shape with the centre position
        shape.setPosition(this->centre);
        shapes.push_back(shape);
        // TODO: here's where we work out if we need additional shapes and add them
        return std::vector<sf::CircleShape>(1, shape);
    }

    bool Hexagon::is_dead() const {
        /*
         * Return true/false on whether this hexagon is finished, based on
         * birth time, current time, start size and decay time
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
