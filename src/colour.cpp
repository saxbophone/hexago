#include <cmath>
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
        double x; // range is 0.0 -> 95.047
        double y; // range is 0.0 -> 100.000
        double z; // range is 0.0 -> 108.883
        double alpha; // range is 0.0 -> 1.0
    } xyz_colour_t;

    /*
     * prototype the internal private function for
     * LAB+Alpha -> CIE 1931/XYZ+Alpha
     */
    static xyz_colour_t xyz_a_from_lab_a(lab_colour_t input);

    /*
     * prototype the internal private function for
     * CIE 1931/XYZ+Alpha -> RGBA (sf::Color)
     */
    static sf::Color colour_from_xyz_a(xyz_colour_t input);

    // returns an RGBA sf::Color instance for the given HSV+A colour
    // algorithm: http://www.easyrgb.com/index.php?X=MATH&H=21#text21
    sf::Color colour_from_hsv_a(hsv_colour_t input) {
        // if saturation is 0, then we can return early
        if(input.s == 0.0) {
            return sf::Color(
                (uint8_t)(input.v * 255.0),
                (uint8_t)(input.v * 255.0),
                (uint8_t)(input.v * 255.0),
                (uint8_t)(input.alpha * 255.0)
            );
        } else {
            double temp_h = input.h * 6;
            // h value must be snapped to range 0.0 -> 6.0
            if(temp_h >= 6.0) {
                temp_h -= 6.0;
            }
            // floor convert to int
            uint8_t temp_i = (uint8_t)temp_h;
            // this further lot of temporaries are used in the channel multiplex
            double temp_a = input.v * (1.0 - input.s);
            double temp_b = input.v * (1.0 - input.s * (temp_h - temp_i));
            double temp_c = input.v * (
                1.0 - input.s * (1.0 - (temp_h - temp_i))
            );
            // prepare variables to hold the double RGB values for later use
            double r, g, b;
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
            // return a colour instance, after converting doubles to ints
            return sf::Color(
                (uint8_t)(r * 255.0),
                (uint8_t)(g * 255.0),
                (uint8_t)(b * 255.0),
                (uint8_t)(input.alpha * 255.0)
            );
        }
    }

    // returns an RGBA sf::Color instance for the given LAB+A colour
    sf::Color colour_from_lab_a(lab_colour_t input) {
        // get xyz_a colour from lab_a colour then convert to rgba
        return colour_from_xyz_a(xyz_a_from_lab_a(input));
    }

    /*
     * private function, returns a CIE 1931 (XYZ) + Alpha colour instance for
     * the given LAB+A colour
     * algorithm: http://www.easyrgb.com/index.php?X=MATH&H=08#text8
     */
    static xyz_colour_t xyz_a_from_lab_a(lab_colour_t input) {
        // Observer = 2°, Illuminant = D65
        const static double ref_x = 95.047;
        const static double ref_y = 100.0;
        const static double ref_z = 108.883;
        // skew input values
        double temp_y = (input.l + 16.0) / 116.0;
        double temp_x = input.a / 500.0 + temp_y;
        double temp_z = temp_y - input.b / 200.0;
        // calculate cube power of each channel
        double temp_y_cubed = pow(temp_y, 3.0);
        double temp_x_cubed = pow(temp_x, 3.0);
        double temp_z_cubed = pow(temp_z, 3.0);
        // multiplex values
        if(temp_y_cubed > 0.008856) {
            temp_y = temp_y_cubed;
        } else {
            temp_y = (temp_y - 16 / 116) / 7.787;
        }
        if(temp_x_cubed > 0.008856) {
            temp_x = temp_x_cubed;
        } else {
            temp_x = (temp_x - 16 / 116) / 7.787;
        }
        if(temp_z_cubed > 0.008856) {
            temp_z = temp_z_cubed;
        } else {
            temp_z = (temp_z - 16 / 116) / 7.787;
        }
        // adjust the output results for observer calibration, use alpha as-is
        xyz_colour_t output = {
            ref_x * temp_x, ref_y * temp_y, ref_z * temp_z, input.alpha,
        };
        return output;
    }

    /*
     * private function, an RGBA sf::Color instance for the given CIE 1931 (XYZ)
     * + Alpha colour
     * algorithm: http://www.easyrgb.com/index.php?X=MATH&H=01#text1
     */
    static sf::Color colour_from_xyz_a(xyz_colour_t input) {
        // shrink larger numbers down to float values
        double temp_x = input.x / 100.0;
        double temp_y = input.y / 100.0;
        double temp_z = input.z / 100.0;
        // multiplex the values
        double temp_r = temp_x *  3.2406 + temp_y * -1.5372 + temp_z * -0.4986;
        double temp_g = temp_x * -0.9689 + temp_y *  1.8758 + temp_z *  0.0415;
        double temp_b = temp_x *  0.0557 + temp_y * -0.2040 + temp_z *  1.0570;
        // clamp values
        if(temp_r > 0.0031308) {
            temp_r = 1.055 * (pow(temp_r, (1.0 / 2.4))) - 0.055;
        } else {
            temp_r = 12.92 * temp_r;
        }
        if(temp_g > 0.0031308) {
            temp_g = 1.055 * (pow(temp_g, (1.0 / 2.4))) - 0.055;
        } else {
            temp_g = 12.92 * temp_g;
        }
        if(temp_b > 0.0031308) {
            temp_b = 1.055 * (pow(temp_b, (1.0 / 2.4))) - 0.055;
        } else {
            temp_b = 12.92 * temp_b;
        }
        // return a colour instance, after converting doubles to ints
        return sf::Color(
            (uint8_t)(temp_r * 255.0),
            (uint8_t)(temp_g * 255.0),
            (uint8_t)(temp_b * 255.0),
            (uint8_t)(input.alpha * 255.0)
        );
    }

}
