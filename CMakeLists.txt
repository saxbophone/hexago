# begin basic metadata
cmake_minimum_required(VERSION 3.0)

project(hexago VERSION 0.7.0 LANGUAGES CXX)
# set build number - this increments for any new version
set(HEXAGO_VERSION_BUILD 10)

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
add_definitions(-DHEXAGO_VERSION_BUILD=${HEXAGO_VERSION_BUILD})
add_definitions(-DHEXAGO_VERSION_STRING=${HEXAGO_ESCAPED_VERSION_STRING})

message(
    STATUS
    "[hexago] Preparing to build Hexago v${HEXAGO_VERSION_STRING} "
    "(build ${HEXAGO_VERSION_BUILD})"
)

# set default C++ standard to use (C++11)
set(HEXAGO_CXX_STANDARD "11")
# if env variable HEXAGO_CXX_STANDARD is set, override version
if(DEFINED ENV{HEXAGO_CXX_STANDARD})
    set(HEXAGO_CXX_STANDARD "$ENV{HEXAGO_CXX_STANDARD}")
endif()
message(STATUS "[hexago] C++ Standard set to C++${HEXAGO_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD ${HEXAGO_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    message(STATUS "[hexago] Warnings Enabled")
    # enable all warnings about 'questionable constructs'
    enable_cxx_compiler_flag_if_supported("-Wall")
    # issue 'pedantic' warnings for strict ISO compliance
    enable_cxx_compiler_flag_if_supported("-pedantic")
    # enable 'extra' strict warnings
    enable_cxx_compiler_flag_if_supported("-Wextra")
    # convert all warnings into errors
    enable_cxx_compiler_flag_if_supported("-Werror")
endif()

# default build type is only static if on Windows
if(WIN32)
    set(HEXAGO_STATIC_BUILD ON CACHE BOOL "")
else()
    set(HEXAGO_STATIC_BUILD OFF CACHE BOOL "")
endif()

# do necessary things if static build was requested
if(HEXAGO_STATIC_BUILD)
    message(STATUS "[hexago] Performing a Static Build")
    set(SFML_STATIC_LIBRARIES ON)
endif()

# unset BUILD_SHARED_LIBS, in case it was set
# this affects whether *we* build as static or shared
# in this instance, we always want to build libhexago as a static library as
# we're not going to install it separately at all and want to bundle it with
# all executables that depend on it
unset(BUILD_SHARED_LIBS)

# dependencies
# add custom dependencies directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
# SDL2
find_package(SFML 2 REQUIRED COMPONENTS audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})
# COLRCV
find_package(COLRCV 0.1 REQUIRED)
include_directories(${COLRCV_INCLUDE_DIR})
# if on OSX, then we also need to find the Foundation and Screensaver frameworks
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_library(OSX_FRAMEWORK_FOUNDATION Foundation)
    find_library(OSX_FRAMEWORK_SCREENSAVER ScreenSaver)
endif()

# compile the bulk of Hexago into a library (libhexago)
# this is then shared among the programs which depend on it

# libhexago C++ Sources
file(GLOB LIBHEXAGO_SOURCES "hexago/*.cpp")
# libhexago Headers
file(GLOB LIBHEXAGO_HEADERS "hexago/*.hpp")

# here we define the libhexago library
add_library(hexago ${LIBHEXAGO_SOURCES})

# if we're on windows, then set these additional linker options so the console
# window doesn't show up and get in the way
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,windows")
endif()

# here we link libhexago with its dependencies
# we need to do additional linking steps if it's a static build
if(HEXAGO_STATIC_BUILD)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        # if we're using GCC then these are the flags we need to use to enable
        # statically linking the C and C++ standard libraries
        #
        # this is useful if it's unlikely a recipient of the software will
        # have the correct versions of these on their system (e.g. MinGW
        # compiling for Windows)
        #
        # This is allowed as per the GCC Runtime Exception.
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    endif()
    # if we're statically linking, then we need to manually link SFML's dependencies as well
    target_link_libraries(hexago ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${COLRCV_LIBRARIES})
else()
    # if we're dynamically linking, we only need to link SFML and COLRCV
    target_link_libraries(hexago ${SFML_LIBRARIES} ${COLRCV_LIBRARIES})
endif()

# specify executables and link with the library
# this is the cross-platform demo program
add_executable(hexago-demo "demo.cpp")
target_link_libraries(hexago-demo hexago)
# include Windows NT Screensaver if we're on Windows NT
if(WIN32)
    add_executable(hexago-win "windows_nt.cpp")
    # make the executable file have a '.scr' file extension
    set_target_properties(hexago-win PROPERTIES SUFFIX ".scr")
    # as well as hexago library, we also need to link to the windows scrnsave.lib library
    target_link_libraries(hexago-win hexago scrnsave)
endif()
# include Mac OSX Screensaver if we're on Mac OSX
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # make sure CMake passes the correct arguments to the compiler to build as
    # objective-c++, and to enable ARC (rather than garbage collection)
    set_source_files_properties(
        "mac_osx.mm" PROPERTIES COMPILE_FLAGS "-x objective-c++ -fobjc-arc"
    )
    # OSX Screensavers are built as bundles (a kind of library), as they need
    # to be loaded into the OS as a plugin rather than run of their own accord
    add_library(Hexago MODULE "mac_osx.mm")
    set_target_properties(Hexago PROPERTIES BUNDLE TRUE BUNDLE_SUFFIX "saver")
    # link it with hexago, as well as OSX Foundation and ScreenSaver frameworks
    target_link_libraries(Hexago hexago ${OSX_FRAMEWORK_FOUNDATION} ${OSX_FRAMEWORK_SCREENSAVER} objc)
    # TODO: Set up creation of App Bundle containing dependencies for portability
endif()

install(TARGETS hexago-demo DESTINATION bin)
