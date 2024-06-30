#include "../defs.h"
#include "../structs.h"
#include <SDL2/SDL_render.h>

extern App app;

extern float zoom_x;
extern float zoom_y;
extern float ratio;
extern float horz_offset;
extern int screen_width;
extern int screen_height;

void prepare_scene(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
    SDL_RenderClear(app.renderer);
}

void present_scene() { SDL_RenderPresent(app.renderer); }

void update_window() {
    if (SDL_GetRendererOutputSize(app.renderer, &screen_width, &screen_height) < 0) {
        printf("Couldn't retrieve window size with error: %s\n", SDL_GetError());
        return; // non-critical, we can just return
    }

    ratio = (float)screen_width / (float)screen_height;
    zoom_x = ((float)screen_width / DEFAULT_SCREEN_WIDTH) * (DEFAULT_RATIO / ratio);
    zoom_y = (float)screen_height / DEFAULT_SCREEN_HEIGHT;

    /* if (SDL_RenderSetScale(app.renderer, zoom_x, zoom_y) < 0) { */
    /*     printf("Coulnd't set renderer scale with error: %s\n", SDL_GetError()); */
    /*     return; */
    /* } */
}

void render_point(Vector2 point, Colour col) {
    if (SDL_SetRenderDrawColor(app.renderer, col.r, col.g, col.b, col.a) < 0) {
        printf("Couldn't set draw colour with error: %s\n", SDL_GetError());
        exit(1);
    }
    if (SDL_RenderDrawPointF(app.renderer, point.x, point.y) < 0) {
        printf("Couldn't render point with error: %s\n", SDL_GetError());
        exit(1);
    }
}

void render_line(int x1, int y1, int x2, int y2, Colour col) {
    if (SDL_SetRenderDrawColor(app.renderer, col.r, col.g, col.b, col.a) < 0) {
        printf("Couldn't set draw colour with error: %s\n", SDL_GetError());
        exit(1);
    }
    if (SDL_RenderDrawLineF(app.renderer, x1, y1, x2, y2) < 0) {
        printf("Couldn't render line with error: %s\n", SDL_GetError());
    }
}

void render_polygon(Vector2 *vectors, int count, Colour col) {
    // convert vectors to points
    SDL_FPoint points[count];
    for (int i = 0; i < count; i++) {
        SDL_FPoint point = {vectors[i].x, vectors[i].y};
        points[i] = point;
    }

    if (SDL_SetRenderDrawColor(app.renderer, col.r, col.g, col.b, col.a) < 0) {
        printf("Couldn't set draw colour with error: %s\n", SDL_GetError());
        exit(1);
    }
    if (SDL_RenderDrawLinesF(app.renderer, points, count) < 0) {
        printf("Coulnd't render polygon with error: %s\n", SDL_GetError());
        exit(1);
    }
}
