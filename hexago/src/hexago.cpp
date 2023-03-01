#include <SFML/Graphics/Color.hpp>

#include "hexago/hexago.hpp"


// Version numbers are passed as preprocessor definitions by CMake
const hexago::version_t hexago::VERSION = {
    HEXAGO_VERSION_MAJOR,
    HEXAGO_VERSION_MINOR,
    HEXAGO_VERSION_PATCH,
    HEXAGO_VERSION_BUILD,
    HEXAGO_VERSION_STRING,
};

// program copyright notice
const char* hexago::copyright = HEXAGO_COPYRIGHT_STRING;

sf::Color hexago::convert_colour_to_rgb(colour_t colour) {
    // XXX: currently disregards colour conversion and always takes RGB colours
    // don't forget to include the alpha channel when creating the SFML colour
    return sf::Color(
        colour.d_channel, // r
        colour.e_channel, // g
        colour.f_channel, // b
        /*
         * alpha is given as range from 0..100 but SFML wants 0..255 so scale
         * the alpha channel
         */
        colour.alpha_channel / 100.0 * 255
    );
}
