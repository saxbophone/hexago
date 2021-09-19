#ifndef SAXBOPHONE_HEXAGO_HEXAGO_HPP
#define SAXBOPHONE_HEXAGO_HEXAGO_HPP

#include <cstdint>

#include <SFML/Graphics/Color.hpp>


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

    /*
     * enum for expressing which colour model should be used to represent the
     * colour ranges of the hexagons to be generated
     * NOTE: currently ignored, colours are always in RGB
     */
    enum colour_model_t {
        COLOUR_MODEL_RGB, // RGB+Alpha
        COLOUR_MODEL_HSV, // HSV+Alpha
        COLOUR_MODEL_LAB, // LAB+Alpha
    };

    typedef double colour_channel_t;

    /*
     * convenience struct type to allow passing around colours in different
     * models without tying the code to one data type
     */
    typedef struct colour_t {
        colour_model_t model; // what model this colour is in
        // the colour channels (see HexagonFactoryConfig.hpp for details)
        colour_channel_t d_channel;
        colour_channel_t e_channel;
        colour_channel_t f_channel;
        colour_channel_t alpha_channel;
    } generic_colour_t;

    extern const version_t VERSION;

    extern const char* copyright;

    /*
     * Converts a colour in any one of the RGB, HSV or LAB colour spaces into
     * an SFML-native RGB colour
     * Note colour_t is currently always RGB, regardless of what colour model
     * it is labelled as.
     */
    sf::Color convert_colour_to_rgb(colour_t colour);

}

#endif // include guard
