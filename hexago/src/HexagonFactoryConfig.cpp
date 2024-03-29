#include <cmath>

#include "hexago/ParameterRange.hpp"
#include "hexago/HexagonFactoryConfig.hpp"
#include "hexago/Hexagon.hpp"


namespace hexago {

    // stores the range bounds of a given colour model in the referenced vars
    static void get_colour_model_range(
        colour_model_t colour_model,
        ParameterRange<colour_channel_t>& d_channel_bounds,
        ParameterRange<colour_channel_t>& e_channel_bounds,
        ParameterRange<colour_channel_t>& f_channel_bounds
    ) {
        // XXX: disregard colour model --always RGB
        // r
        d_channel_bounds.min = 0;
        d_channel_bounds.max = 255;
        // g
        e_channel_bounds.min = 0;
        e_channel_bounds.max = 255;
        // b
        f_channel_bounds.min = 0;
        f_channel_bounds.max = 255;
    }

    // sets a given channel value to the value of check if it is NAN
    static void clamp_if_nan(colour_channel_t& input, colour_channel_t check) {
        if(std::isnan(input)) {
            input = check;
        }
    }

    // constructor
    HexagonFactoryConfig::HexagonFactoryConfig(
        ParameterRange<hexagon_size_t> start_size_range,
        ParameterRange<hexagon_decay_t> decay_speed_range,
        colour_model_t colour_model,
        ParameterRange<colour_channel_t> d_colour_channel_range,
        ParameterRange<colour_channel_t> e_colour_channel_range,
        ParameterRange<colour_channel_t> f_colour_channel_range,
        ParameterRange<colour_channel_t> alpha_colour_channel_range
    )
      : start_size_range(start_size_range)
      , decay_speed_range(decay_speed_range)
      , colour_model(colour_model)
      , d_colour_channel_range(d_colour_channel_range)
      , e_colour_channel_range(e_colour_channel_range)
      , f_colour_channel_range(f_colour_channel_range)
      , alpha_colour_channel_range(alpha_colour_channel_range)
      {}

    // validates any unresolved members of the config struct (i.e. NANs)
    void HexagonFactoryConfig::resolve_defaults() {
        /*
         * check if any of the colour channel values are NAN, and if they are
         * then set them to the default value for that channel, according to
         * which colour model is in use
         */
        ParameterRange<colour_channel_t> d_channel_bounds;
        ParameterRange<colour_channel_t> e_channel_bounds;
        ParameterRange<colour_channel_t> f_channel_bounds;
        // check which colour model we're using, set bounds accordingly
        get_colour_model_range(
            this->colour_model,
            d_channel_bounds,
            e_channel_bounds,
            f_channel_bounds
        );
        // check any channel values for NANs and set them to bounds if so
        clamp_if_nan(this->d_colour_channel_range.min, d_channel_bounds.min);
        clamp_if_nan(this->d_colour_channel_range.max, d_channel_bounds.max);
        clamp_if_nan(this->e_colour_channel_range.min, e_channel_bounds.min);
        clamp_if_nan(this->e_colour_channel_range.max, e_channel_bounds.max);
        clamp_if_nan(this->f_colour_channel_range.min, f_channel_bounds.min);
        clamp_if_nan(this->f_colour_channel_range.max, f_channel_bounds.max);
    }

}
