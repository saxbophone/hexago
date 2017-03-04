#ifndef SAXBOPHONE_HEXAGO_HEXAGON_FACTORY_CONFIG_HPP
#define SAXBOPHONE_HEXAGO_HEXAGON_FACTORY_CONFIG_HPP

#include <SFML/System/Vector2.hpp>

#include "ParameterRange.hpp"
#include "Hexagon.hpp"


namespace hexago {

    /*
     * enum for expressing which colour model should be used to represent the
     * colour ranges of the hexagons to be generated
     */
    enum colour_model_t {
        COLOUR_MODEL_RGB, // RGB+Alpha
        COLOUR_MODEL_HSV, // HSV+Alpha
        COLOUR_MODEL_LAB, // LAB+Alpha
    };

    typedef double colour_channel_t;

    /*
     * A struct type used for holding all the parameters needed to initialise
     * and configure a HexagonFactory
     */
    struct HexagonFactoryConfig {
        ParameterRange<double> start_size_range;
        ParameterRange<double> decay_speed_range;
        colour_model_t colour_model;
        /*
         * the following four properties give the maximum and minimum values
         * that each colour channel may have. The colour system being used may
         * be one of RGB+A, HSV+A or CIEL*a*b+A, so the valid range of these is
         * dependent upon what system is being used. To simplify things, the
         * types of all of these are double to cover the range of every colour
         * system being used.
         *
         * channel mappings:
         * d = R/H/L, e = G/S/a, f = B/V/b - alpha is alpha at all times.
         */
        ParameterRange<colour_channel_t> d_colour_channel_range;
        ParameterRange<colour_channel_t> e_colour_channel_range;
        ParameterRange<colour_channel_t> f_colour_channel_range;
        ParameterRange<colour_channel_t> alpha_colour_channel_range;

        // constructor
        HexagonFactoryConfig(
            ParameterRange<double> start_size_range,
            ParameterRange<double> decay_speed_range,
            colour_model_t colour_model,
            ParameterRange<colour_channel_t> d_colour_channel_range,
            ParameterRange<colour_channel_t> e_colour_channel_range,
            ParameterRange<colour_channel_t> f_colour_channel_range,
            ParameterRange<colour_channel_t> alpha_colour_channel_range
        );
    };

}

#endif // include guard
