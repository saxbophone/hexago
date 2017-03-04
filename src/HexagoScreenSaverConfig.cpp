#include <cstdint>

#include <SFML/Graphics.hpp>

#include "HexagoScreenSaverConfig.hpp"
#include "ParameterRange.hpp"
#include "HexagonFactory.hpp"
#include "Hexagon.hpp"


namespace hexago {

    // main constructor
    HexagoScreenSaverConfig::HexagoScreenSaverConfig(
        ParameterRange<double> start_size_range,
        ParameterRange<double> decay_speed_range,
        colour_model_t colour_model,
        ParameterRange<colour_channel_t> d_colour_channel_range,
        ParameterRange<colour_channel_t> e_colour_channel_range,
        ParameterRange<colour_channel_t> f_colour_channel_range,
        ParameterRange<colour_channel_t> alpha_colour_channel_range,
        unsigned int framerate,
        double minimum_screen_cover,
        hexagon_spawn_mode_t spawn_mode,
        background_colour_t background_colour
    )
    :
    HexagoScreenSaverConfig(
        HexagonFactoryConfig(
            start_size_range,
            decay_speed_range,
            colour_model,
            d_colour_channel_range,
            e_colour_channel_range,
            f_colour_channel_range,
            alpha_colour_channel_range
        ),
        framerate,
        minimum_screen_cover,
        spawn_mode,
        background_colour
    ) {}

    // delegated constructor
    HexagoScreenSaverConfig::HexagoScreenSaverConfig(
        HexagonFactoryConfig sub_config,
        unsigned int framerate,
        double minimum_screen_cover,
        hexagon_spawn_mode_t spawn_mode,
        background_colour_t background_colour
    )
    :
    HexagonFactoryConfig(sub_config),
    framerate(framerate),
    minimum_screen_cover(minimum_screen_cover),
    spawn_mode(spawn_mode),
    background_colour(background_colour)
    {}

}
