#include "structs.h"

#ifndef GLOBALS_H_
#define GLOBALS_H_

// rendering
extern App app;
extern float zoom_x;
extern float zoom_y;
extern float ratio;
extern int screen_width;
extern int screen_height;

// linked lists
extern struct ParticleNode *particles_head;
extern struct AsteroidNode *asteroids_head;

#endif
