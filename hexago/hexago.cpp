#include "hexago.hpp"


// Version numbers are passed as preprocessor definitions by CMake
const hexago::version_t hexago::VERSION = {
    HEXAGO_VERSION_MAJOR,
    HEXAGO_VERSION_MINOR,
    HEXAGO_VERSION_PATCH,
    HEXAGO_VERSION_BUILD,
    HEXAGO_VERSION_STRING,
};

// program copyright notice
const char* hexago::copyright = HEXAGO_COPYRIGHT_STRING;
