#ifndef ASTEROID_H_
#define ASTEROID_H_
#include "../region.h"
#include "../structs.h"

Asteroid *create_asteroid(struct Region *region);
void set_asteroid(Asteroid *roid,
                  Vector2 pos, Vector2 velocity, float size, float rot);

void insert_asteroid_at_beginning(Asteroid **head, Asteroid *roid);
void insert_asteroid_at_end(Asteroid **head, Asteroid *roid);
void remove_asteroid_from_list(Asteroid **head, Asteroid *ref);

void update_asteroid(Asteroid *roid);
void draw_asteroid(Asteroid *roid);
void update_asteroid_list(Asteroid *head);
void draw_asteroid_list(Asteroid *head);

#endif
