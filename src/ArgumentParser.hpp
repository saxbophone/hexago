#ifndef SAXBOPHONE_HEXAGO_ARGUMENT_PARSER_HPP
#define SAXBOPHONE_HEXAGO_ARGUMENT_PARSER_HPP

#include "HexagoScreenSaverConfig.hpp"


namespace hexago {

    // parse command-line arguments and returns a screen saver config object
    HexagoScreenSaverConfig parse_arguments(int argc, char* argv[]);

}

#endif // include guard
