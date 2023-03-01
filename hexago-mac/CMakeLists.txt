# make sure CMake passes the correct arguments to the compiler to build as
# objective-c++, and to enable ARC (rather than garbage collection)
set_source_files_properties(
    "mac_osx.mm" PROPERTIES COMPILE_FLAGS "-x objective-c++ -fobjc-arc"
)
# OSX Screensavers are built as bundles (a kind of library), as they need
# to be loaded into the OS as a plugin rather than run of their own accord
add_library(hexago-mac MODULE "mac_osx.mm")
set_target_properties(
    hexago-mac PROPERTIES
    OUTPUT_NAME Hexago
    BUNDLE TRUE
    BUNDLE_EXTENSION "saver"
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/mac_osx_bundle_info.plist"
)
# find the Foundation and Screensaver frameworks
find_library(OSX_FRAMEWORK_FOUNDATION Foundation)
find_library(OSX_FRAMEWORK_SCREENSAVER ScreenSaver)
# link with hexago, as well as OSX Foundation and ScreenSaver frameworks and the objective-c runtime
target_link_libraries(hexago-mac hexago ${OSX_FRAMEWORK_FOUNDATION} ${OSX_FRAMEWORK_SCREENSAVER} objc)
