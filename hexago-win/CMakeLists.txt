# if we're building with MinGW in release mode, then set these additional
# linker options so the Windows console window doesn't show up and get in the way
if(MINGW AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,windows")
endif()

add_executable(hexago-win "windows_nt.cpp")
# make the executable file have a '.scr' file extension
set_target_properties(hexago-win PROPERTIES OUTPUT_NAME Hexago SUFFIX ".scr")
# as well as hexago library, we also need to link to the windows scrnsave.lib library
target_link_libraries(hexago-win hexago scrnsave)
