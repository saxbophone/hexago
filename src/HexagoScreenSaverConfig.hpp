#ifndef SAXBOPHONE_HEXAGO_HEXAGO_SCREEN_SAVER_CONFIG_HPP
#define SAXBOPHONE_HEXAGO_HEXAGO_SCREEN_SAVER_CONFIG_HPP

#include <cstdint>

#include <SFML/Graphics.hpp>

#include "HexagonFactory.hpp"
#include "Hexagon.hpp"


namespace hexago {

    // enum for expressing where Hexagons should spawn
    enum hexagon_spawn_mode_t {
        SPAWN_MODE_DEFAULT, // spawn in-place, no re-ordering
        SPAWN_MODE_BOTTOM, // new Hexagons spawn underneath existing ones
        SPAWN_MODE_TOP, // new Hexagons spawn above existing ones
    };

    // enum for expressing what the background colour should be
    enum background_colour_t {
        BG_COLOUR_BLACK, // a solid black background, the default
        BG_COLOUR_WHITE, // a solid white background, not recommended
    };

    /*
     * A struct type used for holding all the parameters needed to initialise
     * and configure a Hexago Screen Saver - inherits many attributes from
     * HexagonFactoryConfig, extending it with attributes which the factory
     * doesn't need to care about.
     */
    struct HexagoScreenSaverConfig: public HexagonFactoryConfig {
        /*
         * this property specifies the minimum amount of the screen area which
         * should be covered by Hexagons at any point in time. Also given as a
         * percentage where 1.0 is 100% and 0.0 is 0%
         */
        float minimum_screen_cover;
        // spawn mode specifier, refer to enum description
        hexagon_spawn_mode_t spawn_mode;
        // background colour mode specifier, refer to enum description
        background_colour_t background_colour;

        // main constructor
        HexagoScreenSaverConfig(
            ParameterRange<float> start_size_range,
            ParameterRange<float> decay_speed_range,
            colour_model_t colour_model,
            ParameterRange<colour_channel_t> d_colour_channel_range,
            ParameterRange<colour_channel_t> e_colour_channel_range,
            ParameterRange<colour_channel_t> f_colour_channel_range,
            ParameterRange<colour_channel_t> alpha_colour_channel_range,
            float minimum_screen_cover,
            hexagon_spawn_mode_t spawn_mode,
            background_colour_t background_colour
        );

        // delegated constructor
        HexagoScreenSaverConfig(
            HexagonFactoryConfig sub_config,
            float minimum_screen_cover,
            hexagon_spawn_mode_t spawn_mode,
            background_colour_t background_colour
        );

    };

}

#endif // include guard
