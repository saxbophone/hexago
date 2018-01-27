#include <string>
#include <sstream>
#include <vector>

#include <cstdio>

#include <SFML/Window.hpp>

#include "hexago/hexago.hpp"
#include "hexago/HexagoScreenSaver.hpp"
#include "hexago/argument_parser.hpp"


static bool keep_running(sf::RenderWindow& window) {
    sf::Event event;
    while(window.pollEvent(event)) {
        switch(event.type) {
            /*
             * any of the following event types in this series of case
             * fall-throughs warrant a program exit.
             */
            case sf::Event::Closed:
            case sf::Event::LostFocus:
            case sf::Event::KeyPressed:
            case sf::Event::MouseWheelScrolled:
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseMoved:
            case sf::Event::TouchBegan:
            case sf::Event::TouchMoved:
            case sf::Event::TouchEnded:
                // return false to indicate it should stop running
                return false;
            default:
                // keep checking events
                break;
        }
    }
    // if no stop events were found, we get here and return true to keep running
    return true;
}

int main(int argc, char* argv[]) {
    // build window title / console 'greet' message
    std::ostringstream window_title_stream;
    window_title_stream << "Hexago v" << hexago::VERSION.string;
    window_title_stream << " (build " << hexago::VERSION.build << ")";
    std::string window_title = window_title_stream.str();
    // print Hexago version and copyright notice, on separate lines
    printf("%s\n%s\n", window_title.c_str(), hexago::copyright);
    /*
     * get screen saver config from command-line arguments, then instantiate a
     * HexagoScreenSaver object from the config (and set internal framelimit to
     * true)
     */
    hexago::HexagoScreenSaver app(hexago::parse_arguments(argc, argv), true);
    // loop while window should keep running
    while(keep_running(app.window)) {
        // call the update method to update internal state and draw the frame
        app.update();
    }
    // close window when finished
    app.window.close();
    return 0;
}
