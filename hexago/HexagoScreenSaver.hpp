#ifndef SAXBOPHONE_HEXAGO_HEXAGO_SCREEN_SAVER_HPP
#define SAXBOPHONE_HEXAGO_HEXAGO_SCREEN_SAVER_HPP

#include <deque>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/WindowHandle.hpp>
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
            /*
             * default constructor -optionally takes a config object or uses
             * the default config otherwise
             * when using this constructor, a full-screen SFML window will be
             * created and the screensaver will render to this
             * internal_framelimit controls whether or not this screensaver
             * class should apply frame-limiting or not. This should be left as
             * `false` if framelimiting is being managed externally (as is the
             * case in screensaver modules for both Microsoft Windows and macOS)
             */
            HexagoScreenSaver(
                HexagoScreenSaverConfig config=resolved_default_config(),
                bool internal_framelimit=false
            );
            /*
             * this constructor takes an OS-specific window handle and will
             * render to that instead -like the default constructor, this one
             * also optionally takes a config object, without which the default
             * config is used
             * internal_framelimit is the same as that mentioned above
             */
            HexagoScreenSaver(
                sf::WindowHandle window_handle,
                HexagoScreenSaverConfig config=resolved_default_config(),
                bool internal_framelimit=false
            );
            /*
             * this constructor takes a reference to an sf::RenderTarget
             * (generic abstract base class of RenderWindow/RenderTexture) to
             * support swappable rendering to a Window or Texture as required
             */
            HexagoScreenSaver(
                sf::RenderTarget& render_target,
                HexagoScreenSaverConfig config=resolved_default_config(),
                bool internal_framelimit=false
            );
            // returns the size of the window we're bound to
            sf::Vector2u window_size() const;
            // returns the size of the window dimension to use for scaling 
            double scaling_dimension() const;
            // updates internal state and renders the hexagons to window
            void update();
            // retrieves the default config
            static HexagoScreenSaverConfig default_config();

            /*
             * The SFML RenderWindow that this screensaver will render to
             */
            sf::RenderWindow window;

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
            // performs additional initialisation after field initialisation
            void init();

            // whether internal framelimiting is enabled or not
            const bool internal_framelimit;
            // where we store the config settings
            HexagoScreenSaverConfig config;
            // a HexagonFactory instance which will be used to produce Hexagons
            HexagonFactory hexagon_factory;
            // the maximum number of Hexagons to draw to the screen at once
            const size_t hexagon_count;
            // the colour to paint the background with
            const sf::Color background_colour;
            /*
             * double-ended-queue to store the Hexagons in
             * a deque is used because it allows faster insertion/removal at
             * either end of the queue
             */
            std::deque<Hexagon> hexagons;
            /*
             * a tuning constant for the mechanics which calculates the number
             * of hexagons which need to be drawn
             */
            static const double HEXAGON_NUMBER_TUNING_CONSTANT;
    };

}

#endif // include guard
