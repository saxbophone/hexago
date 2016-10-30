#include <cmath>
#include <cstdint>

#include "hexagon.hpp"


namespace hexago {

    Hexagon::Hexagon(
        Point centre, hexagon_size_t start_size, hexagon_decay_t decay_rate,
        sdl_timestamp_t birth_time
    ) :
        centre(centre), start_size(start_size), decay_rate(decay_rate),
        birth_time(birth_time), now_time(birth_time), seconds_alive(0.0),
        current_size(start_size) {}

    Hexagon::Hexagon(
        screen_size_t x, screen_size_t y, hexagon_size_t start_size,
        hexagon_decay_t decay_rate, sdl_timestamp_t birth_time
    ) : Hexagon(Point(x, y), start_size, decay_rate, birth_time) {}

    void Hexagon::update(sdl_timestamp_t now) {
        // get milliseconds that have elapsed since birth
        sdl_timestamp_t alive_time_milliseconds = now - this->birth_time;
        // convert to fractional seconds and store in instance variable
        this->seconds_alive = alive_time_milliseconds / 1000.0;
        /*
         * update current size based on current time, birth time, decay time and
         * start size
         */
        this->current_size = (
            (hexagon_size_t)(
                (seconds_alive_t)this->start_size - (
                    (seconds_alive_t)this->decay_rate * this->seconds_alive
                )
            )
        );
    }

    hexagon_points_t Hexagon::points() {
        // build empty hexagon_points struct
        hexagon_points_t points;
        // construct the co-ordinates of each point of the hexagon
        for(uint8_t i = 0; i < 6; i++) {
            // convert angle from degress to radians
            double radians = (PI() / 180.0) * ((60.0 * (double)i) + 30);
            // set values of x/y co-ords in points struct array
            points.points[i] = Point(
                this->centre.x + (this->current_size * cos(radians)),
                this->centre.y + (this->current_size * sin(radians))
            );
        }
        return points;
    }

    bool Hexagon::is_dead() {
        /*
         * TODO: Return true/false on whether this hexagon is finished, based
         * on birth time, current time, start size and decay time
         */
        return (this->current_size <= 0) ? true : false;
    }

}
