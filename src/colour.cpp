#include <cstdint>
#include <cstdlib>

#include "colour.hpp"


namespace hexago {

    /*
     * This struct type is used to represent a XYZ+Alpha Colour
     * (according to the CIE 1931 Colour Space).
     *
     * This type is intended to be used as an intermediate colour space type
     * for converting between the LAB and RGB Colour spaces, as there is no
     * defined calculation for converting directly between LAB and RGB
     */
    typedef struct xyz_colour_t {
        float x; // range is 0.0 -> 95.047
        float y; // range is 0.0 -> 100.000
        float z; // range is 0.0 -> 108.883
        float alpha; // range is 0.0 -> 1.0
    } xyz_colour_t;

    /*
     * prototype the internal private function for
     * LAB+Alpha -> CIE 1931/XYZ+Alpha
     */
    static xyz_colour_t xyz_a_from_lab_a(lab_colour_t input);

    // returns an RGBA sf::Color instance for the given HSV+A colour
    // algorithm: http://www.easyrgb.com/index.php?X=MATH&H=21#text21
    sf::Color colour_from_hsv_a(hsv_colour_t input) {
        // if saturation is 0, then we can return early
        if(input.s == 0.0f) {
            return sf::Color(
                (uint8_t)(input.v * 255.0f),
                (uint8_t)(input.v * 255.0f),
                (uint8_t)(input.v * 255.0f),
                (uint8_t)(input.alpha * 255.0f)
            );
        } else {
            float temp_h = input.h * 6;
            // h value must be snapped to range 0.0 -> 6.0
            if(temp_h >= 6.0f) {
                temp_h -= 6.0f;
            }
            // floor convert to int
            uint8_t temp_i = (uint8_t)temp_h;
            // this further lot of temporaries are used in the channel multiplex
            float temp_a = input.v * (1.0f - input.s);
            float temp_b = input.v * (1.0f - input.s * (temp_h - temp_i));
            float temp_c = input.v * (
                1.0f - input.s * (1.0f - (temp_h - temp_i))
            );
            // prepare variables to hold the float RGB values for later use
            float r, g, b;
            // choose one of many different multiplexes based on value of temp_i
            switch(temp_i) {
                case 0:
                    r = input.v;
                    g = temp_c;
                    b = temp_a;
                    break;
                case 1:
                    r = temp_b;
                    g = input.v;
                    b = temp_a;
                    break;
                case 2:
                    r = temp_a;
                    g = input.v;
                    b = temp_c;
                    break;
                case 3:
                    r = temp_a;
                    g = temp_b;
                    b = input.v;
                    break;
                case 4:
                    r = temp_c;
                    g = temp_a;
                    b = input.v;
                    break;
                case 5:
                    r = input.v;
                    g = temp_a;
                    b = temp_b;
                    break;
                default:
                    /*
                     * This is an error condition. It should not be possible to
                     * ever get here, so complain loudly with an abort if we do.
                     */
                    abort();
            }
            // return a colour instance, after converting floats to ints
            return sf::Color(
                (uint8_t)(r * 255.0f),
                (uint8_t)(g * 255.0f),
                (uint8_t)(b * 255.0f),
                (uint8_t)(input.alpha * 255.0f)
            );
        }
    }

    // returns an RGBA sf::Color instance for the given LAB+A colour
    // algorithm: http://www.easyrgb.com/index.php?X=MATH&H=01#text1
    sf::Color colour_from_lab_a(lab_colour_t input) {
        // get xyz_a colour from lab_a colour first
        xyz_colour_t intermediate = xyz_a_from_lab_a(input);
        // TODO: Write Code!
    }

    /*
     * private function, returns a CIE 1931 (XYZ) + Alpha colour instance for
     * the given LAB+A colour
     * algorithm: http://www.easyrgb.com/index.php?X=MATH&H=08#text8
     */
    static xyz_colour_t xyz_a_from_lab_a(lab_colour_t input) {
        // TODO: Write Code!
    }

}
