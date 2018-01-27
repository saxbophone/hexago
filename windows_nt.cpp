#include <string>
#include <vector>

#include <cstdio>
#include <cstdlib>

#include <SFML/Window.hpp>

#include <windows.h>
#include <scrnsave.h>

#include "hexago/HexagoScreenSaver.hpp"


// windows timer handle
#define HEXAGO_TIMER 1

/*
 * for storing a dynamically-allocated screensaver instance
 * --this can't be automatically allocated because the creation and destruction
 * of it happens in the ScreenSaverProc event-handler
 */
static hexago::HexagoScreenSaver* screensaver = NULL;

// this is the main event-handling function of the windows screensaver framework
extern "C" LONG WINAPI ScreenSaverProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
) {
    switch (message) {
        case WM_CREATE:
            // initialise the screensaver from the window handle
            screensaver = new hexago::HexagoScreenSaver(hWnd);
            // start a window timer -the number is milliseconds of delay
            SetTimer(hWnd, HEXAGO_TIMER, 1000 / 30, NULL);
            break;
        case WM_TIMER:
            if (screensaver != NULL) {
                // render one frame of the screensaver
                screensaver->update();
            }
            break;
        case WM_DESTROY:
            // stop the screensaver
            // kill timer
            KillTimer(hWnd, HEXAGO_TIMER);
            // deallocate the screensaver
            delete screensaver;
            break;
        default:
            // all other unhandled messages are passed to DefScreenSaverProc
            return DefScreenSaverProc(hWnd, message, wParam, lParam);
    }
    // for all the messages that we handle, return 0
    return 0;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
extern "C" BOOL WINAPI ScreenSaverConfigureDialog(
    HWND hDlg,
    UINT message, 
    WPARAM wParam,
    LPARAM lParam
) {
    // there currentl is no dialog so we return false
    return false;
}

extern "C" BOOL WINAPI RegisterDialogClasses(HANDLE dlg) {
    return true;
}
#pragma GCC diagnostic pop
