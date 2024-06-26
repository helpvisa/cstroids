#include "draw.h"
#include "init.h"
#include "input.h"
#include "structs.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

extern App app;

int main(int argc, char *argv[]) {
    memset(&app, 0, sizeof(App));

    init_SDL();
    atexit(cleanup_SDL);

    while(1) {
        prepare_scene();
        catch_input();
        present_scene();
        SDL_Delay(16);
    }

    return 0;
}
