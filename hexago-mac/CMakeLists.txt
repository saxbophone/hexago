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
# link it with hexago, as well as OSX Foundation and ScreenSaver frameworks
target_link_libraries(hexago-mac hexago ${OSX_FRAMEWORK_FOUNDATION} ${OSX_FRAMEWORK_SCREENSAVER} objc)
# This old code for manually copying frameworks into the screensaver bundle shouldn't be needed any more, as we ought to be building SFML fully static and shouldn't need it...
# # we need to fiddle with RPath of the OSX Screensaver so that it'll load the locally-bundled dependencies
# add_custom_command(
#     TARGET hexago-mac
#     POST_BUILD COMMAND
#     ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "@loader_path/../Frameworks/"
#     $<TARGET_FILE:hexago-mac>
# )
# # create the Frameworks directory within the Screensaver bundle
# add_custom_command(
#     TARGET hexago-mac POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E make_directory
#             "${CMAKE_BINARY_DIR}/Hexago.saver/Contents/Frameworks"
# )
# set(THINGS_TO_BUNDLE)
# list(APPEND THINGS_TO_BUNDLE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
# # now actually copy each framework dependency
# foreach(DEPENDENCY_PATH ${THINGS_TO_BUNDLE})
#     if(IS_DIRECTORY ${DEPENDENCY_PATH})
#         message(${DEPENDENCY_PATH})
#         get_filename_component(DEPENDENCY_FILE ${DEPENDENCY_PATH} NAME)
#         add_custom_command(
#             TARGET hexago-mac POST_BUILD
#             COMMAND ${CMAKE_COMMAND} -E copy_directory
#                     ${DEPENDENCY_PATH}
#                     "${CMAKE_BINARY_DIR}/Hexago.saver/Contents/Frameworks/${DEPENDENCY_FILE}"
#         )
#     elseif(EXISTS ${DEPENDENCY_PATH})
#         message(${DEPENDENCY_PATH})
#         get_filename_component(DEPENDENCY_FILE ${DEPENDENCY_PATH} NAME)
#         add_custom_command(
#             TARGET hexago-mac POST_BUILD
#             COMMAND ${CMAKE_COMMAND} -E copy
#                     ${DEPENDENCY_PATH}
#                     "${CMAKE_BINARY_DIR}/Hexago.saver/Contents/Frameworks/${DEPENDENCY_FILE}"
#         )
#     endif()
# endforeach()
