#include <cstdint>
#include <cstdio>

#include <SDL2/SDL.h>

#include "hexagon.hpp"


// set up constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

/*
 * sets everything up and if successful stores window and surface handles to
 * pointer args
 */
static bool init(
    SDL_Window** window_ptr, SDL_Renderer** renderer_ptr, int width, int height
) {
    // initialise SDL, catch error if any
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        // print error message
        fprintf(stderr, "Error initialising SDL: %s\n", SDL_GetError());
        return false;
    } else {
        // init temporary pointers
        SDL_Window* window_handle = NULL;
        SDL_Renderer* screen_renderer = NULL;
        // create window
        window_handle = SDL_CreateWindow(
            "Hexago Demo", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN
        );
        // check if it failed
        if(window_handle == NULL) {
            fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
            return false;
        } else {
            // carry on and create renderer
            screen_renderer = SDL_CreateRenderer(
                window_handle, -1, SDL_RENDERER_ACCELERATED
            );
            if(screen_renderer == NULL) {
                fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
                return false;
            }
        }
        // assign pointers to 'out' arguments
        *window_ptr = window_handle;
        *renderer_ptr = screen_renderer;
        // return success
        return true;
    }
}

// cleanup function for shutting down SDL
void cleanup(
    SDL_Window** window_ptr, SDL_Renderer** renderer_ptr
) {
    // destroy window
    SDL_DestroyWindow(*window_ptr);
    // set to NULL for safety
    *window_ptr = NULL;
    // ditto for renderer
    SDL_DestroyRenderer(*renderer_ptr);
    *renderer_ptr = NULL;
    // quit SDL
    SDL_Quit();
}


int main() {
    // create hexagon object
    hexago::Hexagon hexagon = hexago::Hexagon(
        SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2,
        200, SDL_GetTicks()
    );
    // init window and renderer handle variables
    SDL_Window* window_handle = NULL;
    SDL_Renderer* renderer_handle = NULL;
    // call our init() function
    bool success = init(
        &window_handle, &renderer_handle, SCREEN_WIDTH, SCREEN_HEIGHT
    );
    if(success == true) {
        // set render draw colour to a very dark grey
        SDL_SetRenderDrawColor(renderer_handle, 0x1F, 0x1F, 0x1F, 0xFF);
        // quit flag, init to false
        bool quit = false;
        // event handler pointer
        SDL_Event event_handle;
        // build main loop
        do {
            // handle event queue
            while(SDL_PollEvent(&event_handle) != 0) {
                // check if user requested quit
                if(event_handle.type == SDL_QUIT) {
                    quit = true;
                }
            }
            // if hexagon is 'dead' then don't update
            if(!hexagon.is_dead()) {
                // get hexagon points
                hexagon.update(SDL_GetTicks());
                hexago::hexagon_points_t hexagon_points = hexagon.points();
                // draw hexagon to screen
                for(uint8_t i = 0; i < 6; i++) {
                    SDL_RenderDrawLine(
                        renderer_handle,
                        hexagon_points.points[i].x, hexagon_points.points[i].y,
                        hexagon_points.points[(i + 1) % 6].x,
                        hexagon_points.points[(i + 1) % 6].y
                    );
                }
                // update render surface
                SDL_RenderPresent(renderer_handle);
            }
            // update window
            // SDL_UpdateWindowSurface(window_handle);
            // delay to go easy on the CPU/GPU
            SDL_Delay(50);
        } while(!quit);
    } else {
        // return un-success
        return 1;
    }
    // clean up and return success
    cleanup(&window_handle, &renderer_handle);
    return 0;
}
