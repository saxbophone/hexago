#include <SFML/System/Vector2.hpp>

#include "ParameterRange.hpp"
#include "HexagonFactoryConfig.hpp"
#include "Hexagon.hpp"


namespace hexago {

    // constructor
    HexagonFactoryConfig::HexagonFactoryConfig(
        sf::Vector2f spawn_lower_bound,
        sf::Vector2f spawn_upper_bound,
        ParameterRange<hexagon_size_t> start_size_range,
        ParameterRange<hexagon_decay_t> decay_speed_range,
        colour_model_t colour_model,
        ParameterRange<colour_channel_t> d_colour_channel_range,
        ParameterRange<colour_channel_t> e_colour_channel_range,
        ParameterRange<colour_channel_t> f_colour_channel_range,
        ParameterRange<colour_channel_t> alpha_colour_channel_range
    )
    :
    spawn_lower_bound(spawn_lower_bound),
    spawn_upper_bound(spawn_upper_bound),
    start_size_range(start_size_range),
    decay_speed_range(decay_speed_range),
    colour_model(colour_model),
    d_colour_channel_range(d_colour_channel_range),
    e_colour_channel_range(e_colour_channel_range),
    f_colour_channel_range(f_colour_channel_range),
    alpha_colour_channel_range(alpha_colour_channel_range)
    {}

}
