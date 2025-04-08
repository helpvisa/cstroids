#include <SDL2/SDL.h>

#ifndef STRUCTS_H_
#define STRUCTS_H_

// keys and inputs
typedef struct {
    int left;
    int right;
    int up;
    int shoot;
    int reset;
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
    Vector2 velocity;
    float max_velocity;
    float speed;
    float angle; // in degrees
    float rot_speed;
    Vector2 *offsets;
    int offset_count;
    int shot_cooldown;
} Ship;

typedef struct Particle {
    Vector2 pos;
    Vector2 velocity;
    int lifetime;
    int life;
    Colour col;
    float size;

    struct Particle *next;
} Particle;

typedef struct Asteroid {
    Vector2 pos;
    Vector2 velocity;
    float size;
    float rotation_speed; // in degrees per second
    Vector2 *offsets;
    int offset_count;

    int was_hit;
    Vector2 hit_influence;
    Vector2 hit_pos;

    struct Asteroid *next;
} Asteroid;

typedef struct Bullet {
    Vector2 pos;
    Vector2 velocity;
    Colour col;
    int life;

    struct Bullet *next;
} Bullet;

#endif
