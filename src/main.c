#include "defs.h"
#include "structs.h"
#include "objects/ship.h"
#include "wrap_sdl/draw.h"
#include "wrap_sdl/init.h"
#include "wrap_sdl/input.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

extern App app;

int main(int argc, char *argv[]) {
    memset(&app, 0, sizeof(App));

    init_SDL("CStroids");
    atexit(cleanup_SDL);

    // create a ship
    Vector2 init_pos = {DEFAULT_SCREEN_WIDTH/2.0, DEFAULT_SCREEN_HEIGHT/2.0};
    Vector2 test_offsets[] = {
        {-10, -5},
        {-10, 5},
        {10, 0}
    };
    Ship testship = init_ship(init_pos, test_offsets, 3);

    while(1) {
        // seTup the bg and parse inputs
        prepare_scene(0, 0, 0, 255);
        update_input();

        // update entities
        update_ship(&testship);

        // draw objects
        update_window();
        draw_ship(&testship);

        // present the final rendered scene
        // at a fixed rate of ~62fps
        present_scene();
        SDL_Delay(16);
    }

    return 0;
}
