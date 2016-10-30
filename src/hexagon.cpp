#include "hexagon.hpp"


namespace hexago {

    Hexagon::Hexagon(
        Point centre, hexagon_size_t start_size, hexagon_decay_t decay_rate,
        sdl_timestamp_t birth_time
    ) :
        centre(centre), start_size(start_size), decay_rate(decay_rate),
        birth_time(birth_time) {}

    Hexagon::Hexagon(
        screen_size_t x, screen_size_t y, hexagon_size_t start_size,
        hexagon_decay_t decay_rate, sdl_timestamp_t birth_time
    ) : Hexagon(Point(x, y), start_size, decay_rate, birth_time) {}

    void Hexagon::update(sdl_timestamp_t now) {
        // get milliseconds that have elapsed since birth
        sdl_timestamp_t alive_time_milliseconds = now - this->birth_time;
        // convert to fractional seconds and store in instance variable
        this->seconds_alive = alive_time_milliseconds / 1000.0;
    }

    hexagon_points_t Hexagon::points() {
        hexagon_points_t points = {
            Point(), Point(), Point(), Point(), Point(), Point()
        };
        return points;
    }

    bool Hexagon::is_dead() {
        /*
         * TODO: Return true/false on whether this hexagon is finished, based
         * on birth time, current time, start size and decay time
         */
        return false;
    }

}
