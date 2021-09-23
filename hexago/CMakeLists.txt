add_library(hexago STATIC)
# ALIAS target to export a namespaced target even when building in-tree
add_library(Hexago::hexago ALIAS hexago)
# add source files
add_subdirectory(src)
# library public header files location
target_include_directories(hexago PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# pass in version of project as preprocessor definitions
target_compile_definitions(
    hexago PRIVATE
    -DHEXAGO_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    -DHEXAGO_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    -DHEXAGO_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    -DHEXAGO_VERSION_BUILD=${PROJECT_VERSION_TWEAK}
    -DHEXAGO_VERSION_STRING=${HEXAGO_ESCAPED_VERSION_STRING}
    -DHEXAGO_COPYRIGHT_STRING=${HEXAGO_ESCAPED_COPYRIGHT_STRING}
    -D${HEXAGO_OS_MACRO}
)
# inherit common project compiler options
target_link_libraries(
    hexago
        PRIVATE
            $<BUILD_INTERFACE:hexago-compiler-options>
)
# find and link with SFML
# set(SFML_STATIC_LIBRARIES TRUE)
CPMFindPackage(
    NAME SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.5.1
    EXCLUDE_FROM_ALL YES
    OPTIONS "BUILD_SHARED_LIBS FALSE" # force SFML to build as static lib for ease of distribution
)
target_link_libraries(hexago PUBLIC sfml-graphics)
