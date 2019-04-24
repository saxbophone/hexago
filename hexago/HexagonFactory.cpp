#include <random>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include <colrcv-0/models/rgb.h>
#include <colrcv-0/models/hsv.h>
#include <colrcv-0/models/lab.h>

#include "HexagonFactory.hpp"
#include "HexagonFactoryConfig.hpp"
#include "Hexagon.hpp"
#include "hexago.hpp"


namespace hexago {

    // constructor
    HexagonFactory::HexagonFactory(
        HexagonFactoryConfig& config,
        sf::Vector2u window_size,
        double scaling_dimension
    )
    /*
     * all of the properties are set via an initialiser list, reading from
     * config object. additionally, the window size needs to be known so
     * that the spawn bounds can be configured and the scaling factor needs
     * to be known so that the sizes and speeds may be set relative to this.
     *
     * std::random_device has two parens for a reason:
     * once for constructing the type
     * second for calling it, as that's what will give us random samples
     */
      : random_number_engine(std::mt19937(std::random_device()()))
      , x_spawn_range(0.0, (double)window_size.x)
      , y_spawn_range(0.0, (double)window_size.y)
      , start_size_range(
        scaling_dimension / config.start_size_range.min,
        scaling_dimension / config.start_size_range.max
      )
      , decay_speed_range(
        scaling_dimension / config.decay_speed_range.min,
        scaling_dimension / config.decay_speed_range.max
      )
      , colour_model(config.colour_model)
      , d_colour_channel_range(
        config.d_colour_channel_range.min, config.d_colour_channel_range.max
      )
      , e_colour_channel_range(
        config.e_colour_channel_range.min, config.e_colour_channel_range.max
      )
      , f_colour_channel_range(
        config.f_colour_channel_range.min, config.f_colour_channel_range.max
      )
      , alpha_colour_channel_range(
        config.alpha_colour_channel_range.min,
        config.alpha_colour_channel_range.max
      )
      {}

    // returns a randomly-generated Hexagon instance from the factory
    Hexagon HexagonFactory::next() {
        return Hexagon(
            // random starting position
            sf::Vector2f(
                x_spawn_range(this->random_number_engine),
                y_spawn_range(this->random_number_engine)
            ),
            // random starting size
            start_size_range(this->random_number_engine),
            // random decay speed
            decay_speed_range(this->random_number_engine),
            // use a new random colour
            this->colour()
        );
    }

    // gets a new random colour for a Hexagon, based on the chosen colour model
    sf::Color HexagonFactory::colour() {
        // convert a randomly-generated colour in a colour model to SFML Color
        return convert_colour_to_rgb(this->generate_colour());
    }

    colour_t HexagonFactory::generate_colour() {
        colour_t colour = {
            this->colour_model,
            d_colour_channel_range(this->random_number_engine),
            e_colour_channel_range(this->random_number_engine),
            f_colour_channel_range(this->random_number_engine),
            alpha_colour_channel_range(this->random_number_engine)
        };
        return colour;
    }

}
