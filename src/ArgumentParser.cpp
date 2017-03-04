#include <string>

#include <cstdio>

#include "ArgumentParser.hpp"
#include "HexagoScreenSaverConfig.hpp"
#include "HexagoScreenSaver.hpp"
#include "HexagonFactoryConfig.hpp"


namespace hexago {

    /*
     * module-private function for loading one command-line argument into a
     * variable of type double
     * returns true if the argument was found
     */
    static bool load_double_arg(
        std::string flag,
        std::string argument,
        std::string next_argument,
        double& destination,
        int& advance
    ) {
        // if the argument is the same as the flag
        if(argument == flag) {
            // convert the next argument to double and store at destination
            destination = std::stod(next_argument, NULL);
            // set advance to 1 so we skip the next argument (already handled)
            advance = 1;
            // return true as we found it
            return true;
        } else {
            return false;
        }
    }

    /*
     * module-private function for loading one command-line argument which
     * specifies the colour model to use
     * returns true if the argument was found
     */
    static bool load_colour_arg(
        std::string flag,
        std::string argument,
        hexago::colour_model_t colour_model,
        hexago::colour_model_t& destination
    ) {
        // if the argument is the same as the flag
        if(argument == flag) {
            // store the specified colour model in the destination
            destination = colour_model;
            // return true as we found it
            return true;
        } else {
            return false;
        }
    }

    /*
     * module-private function for loading one command-line argument into a
     * variable of type unsigned int
     * returns true if the argument was found
     */
    static bool load_uint_arg(
        std::string flag,
        std::string argument,
        std::string next_argument,
        unsigned int& destination,
        int& advance
    ) {
        // if the argument is the same as the flag
        if(argument == flag) {
            // convert the next argument to double and store at destination
            destination = std::stoul(next_argument, NULL);
            // set advance to 1 so we skip the next argument (already handled)
            advance = 1;
            // return true as we found it
            return true;
        } else {
            return false;
        }
    }


    /*
     * module-private function for loading one command-line argument which
     * specifies the spawn mode to use
     * returns true if the argument was found
     */
    static bool load_spawn_arg(
        std::string flag,
        std::string argument,
        std::string next_argument,
        hexago::hexagon_spawn_mode_t& destination,
        int& advance
    ) {
        if(argument == flag) {
            // set spawn mode based on string
            if(next_argument == "default") {
                destination = SPAWN_MODE_DEFAULT;
            } else if(next_argument == "bottom") {
                destination = SPAWN_MODE_BOTTOM;
            } else if(next_argument == "top") {
                destination = SPAWN_MODE_TOP;
            }
            // advance by one argument
            advance = 1;
            // return true as we found it
            return true;
        } else {
            return false;
        }
    }

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
            // NOTE: This makes heavy use of boolean-OR short-circuiting
            load_double_arg(
                "-ssmin", argument, next_argument, config.start_size_range.min,
                advance
            ) || load_double_arg(
                "-ssmax", argument, next_argument, config.start_size_range.max,
                advance
            ) || load_double_arg(
                "-dsmin", argument, next_argument, config.decay_speed_range.min,
                advance
            ) || load_double_arg(
                "-dsmax", argument, next_argument, config.decay_speed_range.max,
                advance
            ) || load_colour_arg(
                "-cmrgb", argument, COLOUR_MODEL_RGB, config.colour_model
            ) || load_colour_arg(
                "-cmhsv", argument, COLOUR_MODEL_HSV, config.colour_model
            ) || load_colour_arg(
                "-cmlab", argument, COLOUR_MODEL_LAB, config.colour_model
            ) || load_double_arg(
                "-dcmin", argument, next_argument,
                config.d_colour_channel_range.min, advance
            ) || load_double_arg(
                "-dcmax", argument, next_argument,
                config.d_colour_channel_range.max, advance
            ) || load_double_arg(
                "-ecmin", argument, next_argument,
                config.e_colour_channel_range.min, advance
            ) || load_double_arg(
                "-ecmax", argument, next_argument,
                config.e_colour_channel_range.max, advance
            ) || load_double_arg(
                "-fcmin", argument, next_argument,
                config.f_colour_channel_range.min, advance
            ) || load_double_arg(
                "-fcmax", argument, next_argument,
                config.f_colour_channel_range.max, advance
            ) || load_double_arg(
                "-acmin", argument, next_argument,
                config.alpha_colour_channel_range.min, advance
            ) || load_double_arg(
                "-acmax", argument, next_argument,
                config.alpha_colour_channel_range.max, advance
            ) || load_uint_arg(
                "-frame", argument, next_argument, config.framerate, advance
            ) || load_double_arg(
                "-mincv", argument, next_argument, config.minimum_screen_cover,
                advance
            ) || load_spawn_arg(
                "-spawn", argument, next_argument, config.spawn_mode, advance
            );
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
