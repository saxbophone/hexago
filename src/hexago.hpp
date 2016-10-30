#ifndef SAXBOPHONE_HEXAGO_HEXAGO_HPP
#define SAXBOPHONE_HEXAGO_HEXAGO_HPP

#include <cstdint>


namespace hexago {

    typedef struct version_t {
        uint8_t major;
        uint8_t minor;
        uint8_t patch;
        const char* string;
    } version_t;

    extern const version_t VERSION;

}

#endif // include guard
