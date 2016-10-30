#ifndef SAXBOPHONE_HEXAGO_TYPES_HPP
#define SAXBOPHONE_HEXAGO_TYPES_HPP

#include <cmath>
#include <cstdint>


namespace hexago {

    typedef int32_t screen_size_t;
    typedef uint32_t sdl_timestamp_t;

    // a handy constant value for PI
    constexpr double PI() { return atan(1) * 4; }

}

#endif // include guard
