# begin basic metadata
cmake_minimum_required(VERSION 3.0)

project(hexago VERSION 0.3.0 LANGUAGES CXX)

# set default C++ standard to use (C++11)
set(HEXAGO_CXX_STANDARD "11")
# if env variable HEXAGO_CXX_STANDARD is set, override version
if(DEFINED ENV{HEXAGO_CXX_STANDARD})
    set(HEXAGO_CXX_STANDARD "$ENV{HEXAGO_CXX_STANDARD}")
endif()
message(STATUS "C++ Standard set to C++${HEXAGO_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD ${HEXAGO_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    HEXAGO_VERSION_STRING
    "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
)
set(HEXAGO_ESCAPED_VERSION_STRING "\"${HEXAGO_VERSION_STRING}\"")
# end basic metadata

# pass in version of program as preprocessor definitions
add_definitions(-DHEXAGO_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DHEXAGO_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DHEXAGO_VERSION_PATCH=${PROJECT_VERSION_PATCH})
add_definitions(-DHEXAGO_VERSION_STRING=${HEXAGO_ESCAPED_VERSION_STRING})

# used for enabling additional compiler options if supported
include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
    endif()
endfunction()

# enable extra flags (warnings) if we're not in release mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "Warnings Enabled")
    # enable all warnings about 'questionable constructs'
    enable_cxx_compiler_flag_if_supported("-Wall")
    # issue 'pedantic' warnings for strict ISO compliance
    enable_cxx_compiler_flag_if_supported("-pedantic")
    # enable 'extra' strict warnings
    enable_cxx_compiler_flag_if_supported("-Wextra")
    # convert all warnings into errors
    enable_cxx_compiler_flag_if_supported("-Werror")
endif()

# dependencies
# add custom dependencies directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
# SDL2
find_package(SFML 2 REQUIRED COMPONENTS audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})
# COLRCV
find_package(COLRCV 0.1 REQUIRED)
include_directories(${COLRCV_INCLUDE_DIR})

# C++ Sources
file(GLOB HEXAGO_SOURCES "src/*.cpp")
# C++ Headers
file(GLOB HEXAGO_HEADERS "src/*.hpp")

add_executable(hexago ${HEXAGO_SOURCES})

# we only need to link dependencies if it's a static build
# we want to statically link SFML and the C and C++ standard libraries too as
# it's unlikely a recipient of the software will have these on their system.
#
# This is allowed as per the GCC Runtime Exception.
if(SFML_STATIC_LIBRARIES)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    target_link_libraries(hexago ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${COLRCV_LIBRARIES})
else()
    target_link_libraries(hexago ${SFML_LIBRARIES} ${COLRCV_LIBRARIES})
endif()

install(TARGETS hexago DESTINATION bin)
