#ifndef PARTICLE_HELPERS_H_
#define PARTICLE_HELPERS_H_

#include "../structs.h"
#include "../manager.h"

void create_particle_fan(float shift, Vector2 pos,
                         Colour col, int lifetime, float size,
                         float vel_mult, float rand_mult,
                         struct GameManager *gm);

#endif
