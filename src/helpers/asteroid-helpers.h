#include "../structs.h"

#ifndef ASTEROID_HELPERS_H_
#define ASTEROID_HELPERS_H_

void spawn_child_asteroids(struct AsteroidNode **head, Asteroid *roid, Vector2 influence, float size_diff, int count);

#endif
