#include <iostream>
#include <string>
#include <sstream>

#include <SFML/Window.hpp>

#include <cstdio>
#include <cstdlib>

#include <tchar.h>
#include <windows.h>
#include <scrnsave.h>

#include "hexago/hexago.hpp"
#include "hexago/HexagoScreenSaver.hpp"
#include "hexago/HexagoScreenSaverConfig.hpp"
#include "hexago/HexagonFactoryConfig.hpp"
#include "hexago/ParameterRange.hpp"
#include "hexago/argument_parser.hpp"


#define APP_NAME "Hexago Screensaver"
// window class name likely has to be a global variable
TCHAR window_class_name[] = _T(APP_NAME);


/*
 * this is the windows screensaver event-handling function, which we need to
 * prototype even if we don't use it
 */
LRESULT CALLBACK ScreenSaverProc(
    HWND window_handle, UINT message, WPARAM window_params, LPARAM extra
) {
    return DefWindowProc (window_handle, message, window_params, extra);
}

/*
 * these are other windows callback functions for the config dialog,
 * which we're not using yet
 */
BOOL WINAPI ScreenSaverConfigureDialog(HWND, UINT, WPARAM, LPARAM) {
    return false;
}

BOOL WINAPI RegisterDialogClasses(HANDLE) {
    return true;
}


// simple helper function for handling the windows API GUI stuff
static HWND get_window_handle(
    HINSTANCE app_instance, WNDCLASSEX* window_class, HWND parent_window
) {
    // construct a window class data structure
    window_class->hInstance = app_instance;
    window_class->lpszClassName = window_class_name;
    // this is our event-handler callback function, defined above
    window_class->lpfnWndProc = ScreenSaverProc;
    window_class->style = CS_DBLCLKS; // catch double-clicks
    window_class->cbSize = sizeof(WNDCLASSEX); // set object size
    // use default icon and mouse pointer
    window_class->hIcon = LoadIcon(NULL, IDI_APPLICATION);
    window_class->hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    window_class->hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class->lpszMenuName = NULL; // no menu
    window_class->cbClsExtra = 0; // no extra bytes after window class
    window_class->cbWndExtra = 0; // structure or the window instance
    // use Windows's default colour as the background of the window
    window_class->hbrBackground = (HBRUSH)COLOR_BACKGROUND;
    // try and register the window class. if it fails, print error and quit
    if(!RegisterClassEx(window_class)) {
        fprintf(
            stderr, "Windows API Error: Could not register window class\n"
        );
        exit(1);
    }
    /* if we got here, then the class was registered successfully
     * let's now create and return the window handle
     */
    return CreateWindowEx(
        0, // the extended window style to create it with
        window_class_name, // window class name
        window_class_name, // window title text
        WS_MINIMIZE, // window style
        // window x and y positions - in this case, we let windows decide
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        // window x and y dimensions - again, here we let windows decide
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        // window handle to parent window
        parent_window,
        NULL, // handle to menu - in this case, we don't want one
        app_instance, // handle to current app instance
        NULL // no additional window creation data
    );
}


int WINAPI WinMain(
    HINSTANCE current_app_instance,
    HINSTANCE, // previous_app_instance
    LPSTR, // command_line_arguments,
    int // window_show_mode
) {
    // retrieve command-line arguments
    LPWSTR* arguments = NULL;
    int argument_count = 0;
    arguments = CommandLineToArgvW(GetCommandLineW(), &argument_count);
    // catch parse failure
    if(arguments == NULL) {
        fprintf(stderr, "Unable to parse command-line arguments\n");
        return 1;
    }
    // if there were no arguments, then it's asking for config mode
    if(argument_count < 2) {
        // we currently don't implement this
        return 0;
    }
    // initially set parent window to Desktop - we'll change it if preview mode
    HWND parent_window = HWND_DESKTOP;
    // check argument
    // convert from LPWSTR to C++ wstring to preserve my sanity!
    std::wstring argument = arguments[1];
    if(argument[0] == '/') {
        switch(argument[1]) {
            case 'p':
                /*
                 * this is preview mode, so we need to get parent window handle
                 * from the second command-line argument
                 */
                wprintf(L"%s\n", arguments[2]);
                parent_window = (HWND)std::wcstol(arguments[2], NULL, 10);
            case 's':
                // this is screensaver mode, so we can just continue
                break;
            default:
                return 0;
        }
    }
    // get Windows window handle
    WNDCLASSEX window_class = {};
    HWND window_handle = get_window_handle(
        current_app_instance, &window_class, parent_window
    );
    // hand over the window handle to SFML
    sf::RenderWindow window(window_handle);
    // window settings
    sf::ContextSettings settings;
    // set anti-aliasing
    settings.antialiasingLevel = 8;
    // use SFML to create the screen in fullscreen mode
    // get an appropriate video mode
    sf::VideoMode video_mode = sf::VideoMode::getFullscreenModes()[0];
    window.create(video_mode, APP_NAME, sf::Style::Default, settings);
    // instantiate the screensaver app with this window instance
    hexago::HexagoScreenSaver screensaver(window);
    // loop while window remains open
    while(window.isOpen()) {
        // call the update method to update internal state and draw the frame
        screensaver.update();
    }
    std::cin.get();
    // cleanup before exit
    // destroy window handle
    DestroyWindow(window_handle);
    // unregister our app class
    UnregisterClass(window_class_name, current_app_instance);
    return 0;
}
