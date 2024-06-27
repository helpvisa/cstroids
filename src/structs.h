#include <SDL2/SDL.h>

#ifndef STRUCTS_H_
#define STRUCTS_H_

// math
typedef struct {
    int x;
    int y;
} Vector2;

// rendering
typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

typedef struct {
    int r;
    int g;
    int b;
    int a;
} Colour;

// objects
typedef struct {
    Vector2 pos;
    Vector2 speed;
    int angle;
    Vector2 *offsets;
    int offset_count;
} Ship;

#endif
