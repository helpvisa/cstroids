#include "structs.h"
#include <SDL2/SDL_render.h>

extern App app;

void prepare_scene() {
    SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
    SDL_RenderClear(app.renderer);
}

void present_scene() {
    SDL_RenderPresent(app.renderer);
}
