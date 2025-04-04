#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "../structs.h"
#include "../region.h"
#include "../manager.h"

extern struct ParticleNode *particles_head;

Particle *create_particle(struct Region *region);
void set_particle(Particle *part,
                  Vector2 pos, Vector2 velocity,
                  int lifetime, Colour col, float size);

void insert_particle_at_beginning(Particle **head, Particle *part);
void insert_particle_at_end(Particle **head, Particle *part);
void remove_particle_from_list(Particle **head, Particle *ref);

void update_particle(Particle *part, struct GameManager *gm);
void draw_particle(Particle *part);
void update_particle_list(Particle *head, struct GameManager *gm);
void clean_particle_list(Particle **head, Particle **deposit);
void draw_particle_list(Particle *head);

#endif
