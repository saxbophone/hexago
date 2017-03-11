#ifndef SAXBOPHONE_HEXAGO_HEXAGO_HPP
#define SAXBOPHONE_HEXAGO_HEXAGO_HPP

#include <cstdint>


namespace hexago {

    typedef struct version_t {
        // major, minor and patch are all standard semver
        const uint16_t major;
        const uint16_t minor;
        const uint16_t patch;
        // build is a single-series number which increments for any new version
        const uint16_t build;
        const char* string;
    } version_t;

    extern const version_t VERSION;

    extern const char* copyright;

}

#endif // include guard
