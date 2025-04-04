#ifndef ASTEROID_HELPERS_H_
#define ASTEROID_HELPERS_H_

#include "../structs.h"
#include "../manager.h"

void spawn_child_asteroids(struct GameManager *gm, Asteroid *parent,
                           float size_diff, int count);

#endif
