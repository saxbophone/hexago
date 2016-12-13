#ifndef SAXBOPHONE_HEXAGO_COLOUR_HPP
#define SAXBOPHONE_HEXAGO_COLOUR_HPP

#include <cstdint>

#include <SFML/Graphics/Color.hpp>


namespace hexago {

    /*
     * This struct type is used to represent a HSV+Alpha Colour
     */
    typedef struct hsv_colour_t {
        // all values are in range 0.0 -> 1.0
        float h; // hue
        float s; // saturation
        float v; // value
        float alpha; // alpha
    } hsv_colour_t;

    /*
     * This struct type is used to represent a CIE-L*ab+Alpha Colour
     */
    typedef struct lab_colour_t {
        uint8_t l; // lightness, with range 0 -> 100
        int8_t a; // a component, with range -100 -> 100
        int8_t b; // b component, with range -100 -> 100
        float alpha; // range is 0.0 -> 1.0
    } lab_colour_t;

    // returns an RGBA sf::Color instance for the given HSV+A colour
    sf::Color colour_from_hsv_a(hsv_colour_t input);

    // returns an RGBA sf::Color instance for the given LAB+A colour
    sf::Color colour_from_lab_a(lab_colour_t input);

}

#endif // include guard
