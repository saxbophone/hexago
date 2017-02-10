#ifndef SAXBOPHONE_HEXAGO_HEXAGO_SCREEN_SAVER_HPP
#define SAXBOPHONE_HEXAGO_HEXAGO_SCREEN_SAVER_HPP

#include <deque>

#include <cstdint>

#include <SFML/Graphics.hpp>

#include "HexagoScreenSaverConfig.hpp"
#include "HexagonFactory.hpp"
#include "Hexagon.hpp"


namespace hexago {

    /*
     * Main class which wraps the Hexago Screen Saver as an application.
     */
    class HexagoScreenSaver {
        public:
            // simple constructor - needs a sf::RenderWindow instance at least
            HexagoScreenSaver(sf::RenderWindow& window);
            // customisation constructor - allows different options to be set
            HexagoScreenSaver(
                sf::RenderWindow& window, HexagoScreenSaverConfig config
            );
            // updates internal state and renders the hexagons to window
            void update();
            // retrieves the default config
            static HexagoScreenSaverConfig default_config(
                sf::Vector2u window_size
            );

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
            HexagoScreenSaverConfig config;
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
