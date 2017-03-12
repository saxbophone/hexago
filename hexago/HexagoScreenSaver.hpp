#ifndef SAXBOPHONE_HEXAGO_HEXAGO_SCREEN_SAVER_HPP
#define SAXBOPHONE_HEXAGO_HEXAGO_SCREEN_SAVER_HPP

#include <deque>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

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
            // returns the size of the window we're bound to
            sf::Vector2u window_size() const;
            // returns the size of the window dimension to use for scaling 
            double scaling_dimension() const;
            // updates internal state and renders the hexagons to window
            void update();
            // retrieves the default config
            static HexagoScreenSaverConfig default_config();

        private:
            // retrieves the default config, with all default values resolved
            static HexagoScreenSaverConfig resolved_default_config();
            /*
             * calculates the number of Hexagons that this instance of the
             * screensaver should have, based on the screen area, number of
             * Hexagons and average size of them.
             */
            size_t required_number_of_hexagons() const;

            /*
             * Returns an sf::Color instance representing the colour that the
             * background should be, according to the config object given.
             */
            sf::Color resolve_background_colour() const;

            /*
             * a reference to the window instance that this application is bound
             * to, and which it will draw to. This needs to be a reference so
             * that mutation operations which are done on the Window affect the
             * actual window instance in the scope it was originally declared.
             */
            sf::RenderWindow& window;
            // where we store the config settings
            HexagoScreenSaverConfig config;
            // a HexagonFactory instance which will be used to produce Hexagons
            HexagonFactory hexagon_factory;
            // the maximum number of Hexagons to draw to the screen at once
            const size_t hexagon_count;
            // the colour to paint the background with
            const sf::Color background_colour;
            // vector array to store the Hexagons in
            std::deque<Hexagon> hexagons;
            /*
             * a tuning constant for the mechanics which calculates the number
             * of hexagons which need to be drawn
             */
            static const double HEXAGON_NUMBER_TUNING_CONSTANT;
    };

}

#endif // include guard
