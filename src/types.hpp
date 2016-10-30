#ifndef SAXBOPHONE_HEXAGO_TYPES_HPP
#define SAXBOPHONE_HEXAGO_TYPES_HPP

#include <cmath>
#include <cstdint>


namespace hexago {

    typedef uint16_t screen_size_t;
    typedef uint32_t sdl_timestamp_t;

    // a handy constant value for PI
    constexpr double PI() { return atan(1) * 4; }

    class Point {
        public:
            screen_size_t x;
            screen_size_t y;
            Point();
            Point(screen_size_t x, screen_size_t y);
            void update(screen_size_t x, screen_size_t y);
    };

}

#endif // include guard
