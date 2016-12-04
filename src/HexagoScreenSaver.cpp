#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "HexagoScreenSaver.hpp"
#include "HexagonFactory.hpp"


namespace hexago {

    // simple constructor
    HexagoScreenSaver::HexagoScreenSaver(
        sf::RenderWindow& window
    ) : HexagoScreenSaver(
            window,
            {
                0.083333333, // minimum_hexagon_size
                0.166666666, // maximum_hexagon_size
                0.03125, // minimum_hexagon_decay_speed
                0.0625, // maximum_hexagon_decay_speed
                1.0, // minimum_screen_cover
                SPAWN_MODE_DEFAULT, // spawn_mode
                BG_MODE_BLACK, // background_mode
            }
        ) {}

    // customisation constructor
    HexagoScreenSaver::HexagoScreenSaver(
        sf::RenderWindow& window, screen_saver_config_t config
    ) : window(window), config(config) {
        // get window dimensions
        sf::Vector2f window_size = sf::Vector2f(this->window.getSize());
        // instantiate the HexagonFactory
        this->hexagon_factory = HexagonFactory(
            sf::Vector2f(0.0f, 0.0f), // spawn lower bounds
            window_size, // spawn upper bounds
            window_size.y * this->config.minimum_hexagon_size,
            window_size.y * this->config.maximum_hexagon_size,
            window_size.y * this->config.minimum_hexagon_decay_speed,
            window_size.y * this->config.maximum_hexagon_decay_speed
        );
    }

}
