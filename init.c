#include "defs.h"
#include "structs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

App app = {NULL, NULL};

void init_SDL() {
    int rendererFlags, windowFlags;
    rendererFlags = SDL_RENDERER_ACCELERATED;
    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL with error: %s\n", SDL_GetError());
        exit(1); // exit w/ error
    }

    app.window = SDL_CreateWindow("This is a window", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, windowFlags);
    if (!app.window) {
        printf("Failed to open %d x %d window with error: %s\n", SCREEN_WIDTH,
               SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);
    if (!app.renderer) {
        printf("Failed to create renderer with error: %s\n", SDL_GetError());
        exit(1);
    }
}

void cleanup_SDL() {
    SDL_Quit();
}
