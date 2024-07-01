#include "../structs.h"

#ifndef PARTICLE_H_
#define PARTICLE_H_

extern struct ParticleNode *particles_head;

Particle *create_particle(Vector2 pos, Vector2 velocity, int lifetime, Colour col, float size);
void insert_particle_at_beginning(struct ParticleNode **head, Particle *part);
void insert_particle_at_end(struct ParticleNode **head, Particle *part);
void remove_particle_from_list(struct ParticleNode **head, struct ParticleNode **ref);
void update_particle(struct ParticleNode **ref);
void draw_particle(struct ParticleNode *ref);
void update_particle_list(struct ParticleNode **head);
void draw_particle_list(struct ParticleNode *head);

#endif
