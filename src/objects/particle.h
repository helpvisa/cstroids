#include "../structs.h"

#ifndef PARTICLE_H_
#define PARTICLE_H_

extern struct ParticleNode *particles_head;

Particle *create_particle(Vector2 pos, Vector2 velocity, int lifetime, Colour col);
void insert_particle_at_beginning(struct ParticleNode **head, Particle *part);
void insert_particle_at_end(struct ParticleNode **head, Particle *part);
void update_particle(Particle *part);
void draw_particle(Particle *part);
void update_particle_list(struct ParticleNode **head);
void draw_particle_list(struct ParticleNode **head);

#endif
