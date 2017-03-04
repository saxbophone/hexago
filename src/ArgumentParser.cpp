#include <string>

#include <cstdio>

#include "ArgumentParser.hpp"
#include "HexagoScreenSaverConfig.hpp"
#include "HexagoScreenSaver.hpp"
#include "HexagonFactoryConfig.hpp"


namespace hexago {

    /*
     * module-private function for parsing an argument and modifying config in
     * place - returns the number of indexes to skip in the arguments array
     */
    static int parse_argument(
        int arg_index,
        int arg_count,
        char* arguments[],
        HexagoScreenSaverConfig& config
    ) {
        int advance = 0; // the number of indexes to additionally advance
        int next = arg_index + 1; // the index of the next argument
        // convert current and next arguments to C++ strings
        std::string argument = arguments[arg_index];
        std::string next_argument = arguments[next];
        /*
         * if it starts with a hyphen and there's at least one more argument
         * after it, then it may be an argument
         */
        if((argument[0] == '-') && ((next) < arg_count)) {
            // check its value for anything meaningful
            if(argument == "-ssmin") {
                // convert to double
                config.start_size_range.min = std::stod(next_argument, NULL);
                // advance by one argument
                advance = 1;
            } else if(argument == "-ssmax") {
                // convert to double
                config.start_size_range.max = std::stod(next_argument, NULL);
                // advance by one argument
                advance = 1;
            } else if(argument == "-dsmin") {
                // convert to double
                config.decay_speed_range.min = std::stod(next_argument, NULL);
                // advance by one argument
                advance = 1;
            } else if(argument == "-dsmax") {
                // convert to double
                config.decay_speed_range.max = std::stod(next_argument, NULL);
                // advance by one argument
                advance = 1;
            } else if(argument == "-cmrgb") {
                // set colour model to RGB
                config.colour_model = COLOUR_MODEL_RGB;
            } else if(argument == "-cmhsv") {
                // set colour model to HSV
                config.colour_model = COLOUR_MODEL_HSV;
            } else if(argument == "-cmlab") {
                // set colour model to LAB
                config.colour_model = COLOUR_MODEL_LAB;
            } else if(argument == "-dcmin") {
                // convert to double
                config.d_colour_channel_range.min = std::stod(
                    next_argument, NULL
                );
                // advance by one argument
                advance = 1;
            } else if(argument == "-dcmax") {
                // convert to double
                config.d_colour_channel_range.max = std::stod(
                    next_argument, NULL
                );
                // advance by one argument
                advance = 1;
            } else if(argument == "-ecmin") {
                // convert to double
                config.e_colour_channel_range.min = std::stod(
                    next_argument, NULL
                );
                // advance by one argument
                advance = 1;
            } else if(argument == "-ecmax") {
                // convert to double
                config.e_colour_channel_range.max = std::stod(
                    next_argument, NULL
                );
                // advance by one argument
                advance = 1;
            } else if(argument == "-fcmin") {
                // convert to double
                config.f_colour_channel_range.min = std::stod(
                    next_argument, NULL
                );
                // advance by one argument
                advance = 1;
            } else if(argument == "-fcmax") {
                // convert to double
                config.f_colour_channel_range.max = std::stod(
                    next_argument, NULL
                );
                // advance by one argument
                advance = 1;
            } else if(argument == "-acmin") {
                // convert to double
                config.alpha_colour_channel_range.min = std::stod(
                    next_argument, NULL
                );
                // advance by one argument
                advance = 1;
            } else if(argument == "-acmax") {
                // convert to double
                config.alpha_colour_channel_range.max = std::stod(
                    next_argument, NULL
                );
                // advance by one argument
                advance = 1;
            } else if(argument == "-frame") {
                // convert to unsigned int
                config.framerate = std::stoul(next_argument, NULL);
                // advance by one argument
                advance = 1;
            } else if(argument == "-mincv") {
                // convert to double
                config.minimum_screen_cover = std::stod(next_argument, NULL);
                // advance by one argument
                advance = 1;
            } else if(argument == "-spawn") {
                // set spawn mode based on string
                if(next_argument == "default") {
                    config.spawn_mode = SPAWN_MODE_DEFAULT;
                } else if(next_argument == "bottom") {
                    config.spawn_mode = SPAWN_MODE_BOTTOM;
                } else if(next_argument == "top") {
                    config.spawn_mode = SPAWN_MODE_TOP;
                }
                // advance by one argument
                advance = 1;
            }
        }
        return advance;
    }

    HexagoScreenSaverConfig parse_arguments(int argc, char* argv[]) {
        // first of all, get the default config
        HexagoScreenSaverConfig config = HexagoScreenSaver::default_config();
        /*
         * go through all command-line arguments after the first and try and
         * parse their value
         */
        for(int i = 1; i < argc; i++) {
            i += parse_argument(i, argc, argv, config);
        }
        return config;
    }

}
