#ifndef SAXBOPHONE_HEXAGO_MAIN_HPP
#define SAXBOPHONE_HEXAGO_MAIN_HPP

#include <cstdint>


namespace hexago {

    typedef struct version_t {
        const uint8_t major;
        const uint8_t minor;
        const uint8_t patch;
        const char* string;
    } version_t;

    extern const version_t VERSION;

}

#endif // include guard
