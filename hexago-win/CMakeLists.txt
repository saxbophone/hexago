add_executable(hexago-win "windows_nt.cpp")
# make the executable file have a '.scr' file extension
set_target_properties(hexago-win PROPERTIES OUTPUT_NAME Hexago SUFFIX ".scr")
# as well as hexago library, we also need to link to the windows scrnsave.lib library
target_link_libraries(hexago-win hexago scrnsave comctl32)  # comctl32 is also neede on MSVC to prevent linker errors
