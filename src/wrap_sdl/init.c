/*
   Copyright 2025 Daniel Brackenbury

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "../defs.h"
#include "../structs.h"
#include "../globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

extern App app;

void init_SDL(char *window_title) {
    int rendererFlags, windowFlags;
    rendererFlags = SDL_RENDERER_ACCELERATED;
    windowFlags = SDL_WINDOW_RESIZABLE;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL with error: %s\n", SDL_GetError());
        exit(1); // exit w/ error
    }

    app.window = SDL_CreateWindow(window_title,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  DEFAULT_SCREEN_WIDTH,
                                  DEFAULT_SCREEN_HEIGHT,
                                  windowFlags);
    if (!app.window) {
        printf("Failed to open %d x %d window with error: %s\n",
               DEFAULT_SCREEN_WIDTH,
               DEFAULT_SCREEN_HEIGHT,
               SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);
    if (!app.renderer) {
        printf("Failed to create renderer with error: %s\n", SDL_GetError());
        exit(1);
    }

    /* if (SDL_RenderSetLogicalSize(app.renderer, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT) < 0) { */
    /*     printf("Failed to set logical render size with error: %s\n", SDL_GetError()); */
    /*     exit(1); */
    /* } */
}

void cleanup_SDL() { SDL_Quit(); }
