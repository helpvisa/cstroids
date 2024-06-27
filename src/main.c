#include "structs.h"
#include "wrap_sdl/draw.h"
#include "wrap_sdl/init.h"
#include "wrap_sdl/input.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

extern App app;

int main(int argc, char *argv[]) {
    memset(&app, 0, sizeof(App));

    init_SDL();
    atexit(cleanup_SDL);

    while(1) {
        // setup the bg and parse inputs
        prepare_scene(0, 0, 0, 255);
        catch_input();

        // present the final rendered scene
        // at a fixed rate of ~62fps
        present_scene();
        SDL_Delay(16);
    }

    return 0;
}
