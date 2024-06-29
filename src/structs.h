#include <SDL2/SDL.h>

#ifndef STRUCTS_H_
#define STRUCTS_H_

// keys and inputs
typedef struct {
    int left;
    int right;
    int up;
    int shoot;
} InputMap;

// math
typedef struct {
    float x;
    float y;
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
    float angle;
    Vector2 *offsets;
    int offset_count;
} Ship;

#endif
