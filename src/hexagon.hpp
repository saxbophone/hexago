#ifndef SAXBOPHONE_HEXAGO_HEXAGON_HPP
#define SAXBOPHONE_HEXAGO_HEXAGON_HPP

#include <cstdint>

#include <SDL2/SDL.h>

#include "types.hpp"


namespace hexago {

    typedef int32_t hexagon_size_t;
    typedef uint16_t hexagon_decay_t;
    typedef double seconds_alive_t;

    typedef struct hexagon_points_t {
        SDL_Point points[6];
    } hexagon_points_t;

    class Hexagon {
        private:
            // the location of the hexagon on screen
            SDL_Point centre;
            // the start size of the hexagon (radius in pixels)
            hexagon_size_t start_size;
            // how many pixels smaller the hexagon should get in 1 second
            hexagon_decay_t decay_rate;
            // stores the SDL millisecond timestamp that the hexagon was 'born'
            sdl_timestamp_t birth_time;
            // stores the SDL millisecond timestamp for 'now'
            sdl_timestamp_t now_time;
            // stores the fractional seconds this hexagon has been alive for
            seconds_alive_t seconds_alive;
            // stores the current size of the hexagon's radius
            hexagon_size_t current_size;
        public:
            // constructor using x and y co-ordinates for the hexagon position
            Hexagon(
                screen_size_t x, screen_size_t y, hexagon_size_t start_size,
                hexagon_decay_t decay_rate, sdl_timestamp_t birth_time
            );
            // constructor using a Point object for the hexagon position
            Hexagon(
                SDL_Point centre, hexagon_size_t start_size,
                hexagon_decay_t decay_rate, sdl_timestamp_t birth_time
            );
            // updates the hexagon's internal millisecond clock
            void update(sdl_timestamp_t now);
            // returns the points which draw the hexagon at this point in time
            hexagon_points_t points();
            // returns true if this hexagon has finished shrinking
            bool is_dead();
    };

}

#endif // include guard
