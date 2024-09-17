#include "../structs.h"

#ifndef PARTICLE_HELPERS_H_
#define PARTICLE_HELPERS_H_

void create_particle_fan(struct ParticleNode **head, float shift, Vector2 pos, Colour col, int lifetime, float size, float vel_mult, float rand_mult);

#endif
