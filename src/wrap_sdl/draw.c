#include "../structs.h"
#include <SDL2/SDL_render.h>

extern App app;

void prepare_scene(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
    SDL_RenderClear(app.renderer);
}

void present_scene() { SDL_RenderPresent(app.renderer); }

void render_line(int x1, int y1, int x2, int y2, Colour col) {
    if (SDL_SetRenderDrawColor(app.renderer, col.r, col.g, col.b, col.a) < 0) {
        printf("Couldn't set draw colour with error: %s\n", SDL_GetError());
        exit(1);
    }
    if (SDL_RenderDrawLine(app.renderer, x1, y1, x2, y2) < 0) {
        printf("Couldn't render line with error: %s\n", SDL_GetError());
    }
}

void render_polygon(Vector2 *vectors, int count, Colour col) {
    // convert vectors to points
    SDL_Point points[count];
    for (int i = 0; i < count; i++) {
        SDL_Point point = {vectors[i].x, vectors[i].y};
        points[i] = point;
    }

    if (SDL_SetRenderDrawColor(app.renderer, col.r, col.g, col.b, col.a) < 0) {
        printf("Couldn't set draw colour with error: %s\n", SDL_GetError());
        exit(1);
    }
    if (SDL_RenderDrawLines(app.renderer, points, count) < 0) {
        printf("Coulnd't render polygon with error: %s\n", SDL_GetError());
        exit(1);
    }
}
