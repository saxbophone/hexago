#ifndef SAXBOPHONE_HEXAGO_HEXAGO_SCREEN_SAVER_HPP
#define SAXBOPHONE_HEXAGO_HEXAGO_SCREEN_SAVER_HPP

#include <deque>

#include <cstdint>

#include <SFML/Graphics.hpp>

#include "HexagonFactory.hpp"
#include "Hexagon.hpp"


namespace hexago {

    // enum for expressing where Hexagons should spawn
    typedef enum hexagon_spawn_mode_t {
        SPAWN_MODE_DEFAULT = 0, // spawn in-place, no re-ordering
        SPAWN_MODE_BOTTOM, // new Hexagons spawn underneath existing ones
        SPAWN_MODE_TOP, // new Hexagons spawn above existing ones
    } hexagon_spawn_mode_t;

    // enum for expressing what the background colour should be
    typedef enum background_colour_mode_t {
        BG_MODE_BLACK = 0, // a solid black background, the default
        BG_MODE_WHITE, // a solid white background, not recommended
        // background colour set to weighted average of hexagon colours + sizes
        BG_MODE_AVERAGE,
    } background_colour_mode_t;

    /*
     * This struct contains config data for a Hexago Screen Saver instance.
     * It can be used to override the default settings to change the behaviour
     * of the Screensaver.
     */
    typedef struct screen_saver_config_t {
        /*
         * NOTE: The following four properties are given as a proportion to the
         * height of the screen in pixels, where 1.0 is 100% and 0.0 is 0%
         */
        float minimum_hexagon_size;
        float maximum_hexagon_size;
        float minimum_hexagon_decay_speed;
        float maximum_hexagon_decay_speed;
        /*
         * the following eight properties give the maximum and minimum values
         * that each colour channel may have. The colour system being used may
         * be one of RGB+A, HSV+A or CIEL*a*b+A, so the valid range of these is
         * dependent upon what system is being used. To simplify things, the
         * types of all of these are double to cover the range of every colour
         * system being used.
         *
         * channel mappings:
         * d = R/H/L, e = G/S/a, f = B/V/b - alpha is alpha at all times.
         */
        double d_colour_channel_minimum;
        double d_colour_channel_maximum;
        double e_colour_channel_minimum;
        double e_colour_channel_maximum;
        double f_colour_channel_minimum;
        double f_colour_channel_maximum;
        double alpha_colour_channel_minimum;
        double alpha_colour_channel_maximum;
        /*
         * this property specifies the minimum amount of the screen area which
         * should be covered by Hexagons at any point in time. Also given as a
         * percentage where 1.0 is 100% and 0.0 is 0%
         */
        float minimum_screen_cover;
        // spawn mode specifier, refer to enum description
        hexagon_spawn_mode_t spawn_mode;
        // background colour mode specifier, refer to enum description
        background_colour_mode_t background_mode;
    } screen_saver_config_t;

    /*
     * Main class which wraps the Hexago Screen Saver as an application.
     */
    class HexagoScreenSaver {
        public:
            // simple constructor - needs a sf::RenderWindow instance at least
            HexagoScreenSaver(sf::RenderWindow& window);
            // customisation constructor - allows different options to be set
            HexagoScreenSaver(
                sf::RenderWindow& window, screen_saver_config_t config
            );
            // updates internal state and renders the hexagons to window
            void update();

            /*
             * a static constant member which stores the default configuration
             * for the Screen Saver, as screen_saver_config_t struct
             */
            static const screen_saver_config_t DEFAULT_CONFIG;
        private:
            /*
             * calculates the number of Hexagons that this instance of the
             * screensaver should have, based on the screen area, number of
             * Hexagons and average size of them.
             */
            size_t required_number_of_hexagons() const;

            /*
             * a reference to the window instance that this application is bound
             * to, and which it will draw to. This needs to be a reference so
             * that mutation operations which are done on the Window affect the
             * actual window instance in the scope it was originally declared.
             */
            sf::RenderWindow& window;
            // store the window's size as we'll use it later on in other places
            const sf::Vector2u window_size;
            // where we store the config settings
            screen_saver_config_t config;
            // a HexagonFactory instance which will be used to produce Hexagons
            HexagonFactory hexagon_factory;
            // the maximum number of Hexagons to draw to the screen at once
            const size_t hexagon_count;
            // vector array to store the Hexagons in
            std::deque<Hexagon> hexagons;
            /*
             * a tuning constant for the mechanics which calculates the number
             * of hexagons which need to be drawn
             */
            static const float HEXAGON_NUMBER_TUNING_CONSTANT;
    };

}

#endif // include guard
