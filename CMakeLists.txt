# begin basic metadata
# minimum CMake version required for C++20 support, among other things
cmake_minimum_required(VERSION 3.15)

# detect if MyHovercraftIsFullOfEels is being used as a sub-project of another CMake project
if(NOT DEFINED PROJECT_NAME)
    set(HEXAGO_SUBPROJECT OFF)
else()
    set(HEXAGO_SUBPROJECT ON)
endif()

project(hexago VERSION 0.10.0.14 LANGUAGES CXX)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

# Set a default build type if none was specified
set(DEFAULT_BUILD_TYPE "Debug")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# set some handy custom variables to detect Release-type builds from Debug-type ones
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(HEXAGO_BUILD_DEBUG ON)
    set(HEXAGO_BUILD_RELEASE OFF)
else()
    set(HEXAGO_BUILD_DEBUG OFF)
    set(HEXAGO_BUILD_RELEASE ON)
endif()

message(STATUS "[hexago] Build Mode: ${CMAKE_BUILD_TYPE}")

# set the C++ standard to use to C++11 always
set(HEXAGO_CXX_STANDARD "11")
message(STATUS "[hexago] C++ Standard set to C++${HEXAGO_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD ${HEXAGO_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakeDependentOption)
# if building in Release mode, provide an option to explicitly enable tests if desired (always ON for other builds, OFF by default for Release builds)
cmake_dependent_option(ENABLE_TESTS "Build the unit tests in release mode?" OFF HEXAGO_BUILD_RELEASE ON)

# Premature Optimisation causes problems. Commented out code below allows detection and enabling of LTO.
# It's not being used currently because it seems to cause linker errors with Clang++ on Ubuntu if the library
# is compiled with LTO but the unit tests are not. This suggests LTO may force some downstream software into
# using LTO also if it's enabled. The plan is to reënable LTO as an option in the future, possibly done much
# more optionally (and probably not by default).

# include(CheckIPOSupported)
# check_ipo_supported(RESULT IPO_SUPPORTED)
# # If we're in Release mode, set HEXAGO_USE_IPO to ON by default if it's detected as supported (user can always explicitly enable it in Release mode)
# cmake_dependent_option(HEXAGO_USE_IPO "Use Link-Time/Inter-Procedural Optimisation?" ${IPO_SUPPORTED} HEXAGO_BUILD_RELEASE OFF)
# if(HEXAGO_USE_IPO)
#     message(STATUS "[hexago] Link-Time-Optimisation Enabled")
# endif()

set(
    HEXAGO_VERSION_STRING
    "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
)
set(HEXAGO_ESCAPED_VERSION_STRING "\"${HEXAGO_VERSION_STRING}\"")
string(TIMESTAMP CURRENT_YEAR "%Y")
set(HEXAGO_COPYRIGHT_STRING "Copyright (C) ${CURRENT_YEAR} Joshua Saxby. All rights reserved.")
set(HEXAGO_ESCAPED_COPYRIGHT_STRING "\"${HEXAGO_COPYRIGHT_STRING}\"")

# detect OS and set one set of variables for consistency
if(WIN32)
    set(HEXAGO_OS_WINDOWS_NT ON)
    set(HEXAGO_OS_NAME "windows_nt")
    set(HEXAGO_OS_MACRO "HEXAGO_OS_WINDOWS_NT")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(HEXAGO_OS_MAC_OSX ON)
    set(HEXAGO_OS_NAME "mac_osx")
    set(HEXAGO_OS_MACRO "HEXAGO_OS_MAC_OSX")
else() # "other" --it's probably Linux, doesn't matter either way though
    set(HEXAGO_OS_OTHER ON)
    set(HEXAGO_OS_NAME "other")
    set(HEXAGO_OS_MACRO "HEXAGO_OS_OTHER")
endif()
# end basic metadata

if(MINGW)
    # if we're using MinGW then these are the flags we need to use to enable
    # statically linking the C and C++ standard libraries
    #
    # this is useful when it's unlikely a recipient of the software will
    # have the correct versions of these on their system (e.g. MinGW compiling
    # for Windows --recipients who aren't developers probably don't have a copy
    # of libgcc or libstdc++ on their machine that we can link to at runtime)
    #
    # This is allowed as per the GCC Runtime Exception.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -municode")
endif()

# This is a special target which only exists to capture compilation options
# used for hexago and its tests. This is to avoid setting global compiler
# options which would be inherited by dependencies as well, which is bad
# because hexago uses strict compiler warning options which not all other
# projects can build successfully with.
# Any target linked with this one will inherit the compiler options used for
# hexago.
add_library(hexago-compiler-options INTERFACE)

# used for enabling additional compiler options if supported
include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    message(STATUS "[hexago] Checking if compiler supports warning flag '${flag}'")
    check_cxx_compiler_flag("${flag}" flag_supported)
    if(flag_supported)
        message(STATUS "[hexago] Enabling warning flag '${flag}'")
        target_compile_options(hexago-compiler-options INTERFACE "${flag}")
    endif()
    unset(flag_supported CACHE)
endfunction()

# enable a large amount of extra warnings, regardless of build mode
if (MSVC) # MSVC supports different warning options to GCC/Clang
    enable_cxx_compiler_flag_if_supported("/W3")  # set warning level 3
    # if tests are enabled, enable converting all warnings to errors too
    if (ENABLE_TESTS)
        # add_compile_options(/WX)
        enable_cxx_compiler_flag_if_supported("/WX")
    endif()
else() # GCC/Clang warning option
    # NOTE: GCC and Clang support most of the same options, but neither supports all
    # of the others'. By only enabling them if supported, we get graceful failure
    # when trying to enable unsupported flags
    # e.g. at the time of writing, GCC does not support -Wdocumentation
    #
    # enable all warnings about 'questionable constructs'
    enable_cxx_compiler_flag_if_supported("-Wall")
    # issue 'pedantic' warnings for strict ISO compliance
    enable_cxx_compiler_flag_if_supported("-pedantic")
    # enable 'extra' strict warnings
    enable_cxx_compiler_flag_if_supported("-Wextra")
    # enable sign conversion warnings
    enable_cxx_compiler_flag_if_supported("-Wsign-conversion")
    # enable warnings about mistakes in Doxygen documentation
    enable_cxx_compiler_flag_if_supported("-Wdocumentation")
    # if tests are enabled, enable converting all warnings to errors too
    if (ENABLE_TESTS)
        enable_cxx_compiler_flag_if_supported("-Werror")
        # exclude the following kinds of warnings from being converted into errors
        # unknown-pragma is useful to have as a warning but not as an error, if you have
        # pragmas which are for the consumption of one compiler only
        enable_cxx_compiler_flag_if_supported("-Wno-error=unknown-pragmas")
        # unused variable and function warnings are helpful but we don't need them as errors
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-function")
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-variable")
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-parameter")
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-private-field")
        enable_cxx_compiler_flag_if_supported("-Wno-error=unused-but-set-variable")
    endif()
endif()

# add custom dependencies directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

# a better way to load dependencies
include(CPM)

# library
add_subdirectory(hexago)
# this is the cross-platform demo program
add_executable(hexago-demo "demo.cpp")
target_link_libraries(hexago-demo PRIVATE hexago-compiler-options hexago)
# include Windows NT Screensaver if we're on Windows NT
if(HEXAGO_OS_WINDOWS_NT)
    add_subdirectory(hexago-win)
endif()
# include Mac OSX Screensaver if we're on Mac OSX
if(HEXAGO_OS_MAC_OSX)
    add_subdirectory(hexago-mac)
endif()
