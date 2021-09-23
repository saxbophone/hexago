#ifndef SAXBOPHONE_HEXAGO_HEXAGO_SCREEN_SAVER_CONFIG_HPP
#define SAXBOPHONE_HEXAGO_HEXAGO_SCREEN_SAVER_CONFIG_HPP

#include <cstdint>

#include "HexagonFactoryConfig.hpp"
#include "Hexagon.hpp"


namespace hexago {

    // enum for expressing where Hexagons should spawn
    enum hexagon_spawn_mode_t {
        SPAWN_MODE_SAME, // spawn in-place, no re-ordering
        SPAWN_MODE_BOTTOM, // new Hexagons spawn underneath existing ones
        SPAWN_MODE_TOP, // new Hexagons spawn above existing ones
    };

    // enum for expressing what the background colour should be
    enum background_colour_t {
        BG_COLOUR_GREY, // a neutral grey background
        BG_COLOUR_BLACK, // a solid black background
        BG_COLOUR_WHITE, // a solid white background
        BG_COLOUR_NONE, // disable background repainting entirely, shapes blend
        BG_COLOUR_MEDIAN, // pick the colour formed by median of channel ranges
    };

    /*
     * A struct type used for holding all the parameters needed to initialise
     * and configure a Hexago Screen Saver - inherits many attributes from
     * HexagonFactoryConfig, extending it with attributes which the factory
     * doesn't need to care about.
     */
    struct HexagoScreenSaverConfig: public HexagonFactoryConfig {
        unsigned int framerate; // used for SFML framerate-limiting
        unsigned int antialiasing; // antialising level to use, 0 = disabled
        /*
         * this property specifies the minimum amount of the screen area which
         * should be covered by Hexagons at any point in time. Also given as a
         * percentage where 1.0 is 100% and 0.0 is 0%
         */
        double minimum_screen_cover;
        // spawn mode specifier, refer to enum description
        hexagon_spawn_mode_t spawn_mode;
        // background colour mode specifier, refer to enum description
        background_colour_t background_colour;

        // main constructor
        HexagoScreenSaverConfig(
            ParameterRange<hexagon_size_t> start_size_range,
            ParameterRange<hexagon_decay_t> decay_speed_range,
            colour_model_t colour_model,
            ParameterRange<colour_channel_t> d_colour_channel_range,
            ParameterRange<colour_channel_t> e_colour_channel_range,
            ParameterRange<colour_channel_t> f_colour_channel_range,
            ParameterRange<colour_channel_t> alpha_colour_channel_range,
            unsigned int framerate,
            unsigned int antialising,
            double minimum_screen_cover,
            hexagon_spawn_mode_t spawn_mode,
            background_colour_t background_colour
        );

        // delegated constructor
        HexagoScreenSaverConfig(
            HexagonFactoryConfig sub_config,
            unsigned int framerate,
            unsigned int antialising,
            double minimum_screen_cover,
            hexagon_spawn_mode_t spawn_mode,
            background_colour_t background_colour
        );

    };

}

#endif // include guard
