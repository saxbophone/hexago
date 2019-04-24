#include <SFML/Graphics/Color.hpp>

#include <colrcv-0/models/rgb.h>
#include <colrcv-0/models/hsv.h>
#include <colrcv-0/models/lab.h>

#include "hexago.hpp"


// Version numbers are passed as preprocessor definitions by CMake
const hexago::version_t hexago::VERSION = {
    HEXAGO_VERSION_MAJOR,
    HEXAGO_VERSION_MINOR,
    HEXAGO_VERSION_PATCH,
    HEXAGO_VERSION_BUILD,
    HEXAGO_VERSION_STRING,
};

// program copyright notice
const char* hexago::copyright = (
    "Copyright (c) 2017 Joshua Saxby. All rights reserved."
);

sf::Color hexago::convert_colour_to_rgb(colour_t colour) {
    // use libcolrcv to convert from our supported colour models to RGB
    colrcv_rgb_t rgb;
    switch(colour.model) {
        case hexago::COLOUR_MODEL_RGB: {
            // no need to convert this one, but we still need to copy the channels
            rgb.r = colour.d_channel;
            rgb.g = colour.e_channel;
            rgb.b = colour.f_channel;
            break;
        }
        case hexago::COLOUR_MODEL_HSV: {
            // convert from HSV to RGB
            colrcv_hsv_t hsv = {
                colour.d_channel, colour.e_channel, colour.f_channel,
            };
            rgb = colrcv_hsv_to_rgb(hsv);
            break;
        }
        case hexago::COLOUR_MODEL_LAB: {
            // convert from LAB to RGB
            colrcv_lab_t lab = {
                colour.d_channel, colour.e_channel, colour.f_channel,
            };
            rgb = colrcv_lab_to_rgb(lab);
            break;
        }
    }
    // don't forget to include the alpha channel when creating the SFML colour
    return sf::Color(
        rgb.r,
        rgb.g,
        rgb.b,
        /*
         * alpha is given as range from 0..100 but SFML wants 0..255 so scale
         * the alpha channel
         */
        colour.alpha_channel / 100.0 * 255
    );
}
