#include "structs.h"
#include <SDL2/SDL_render.h>

extern App app;

void prepare_scene(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
    SDL_RenderClear(app.renderer);
}

void present_scene() {
    SDL_RenderPresent(app.renderer);
}
