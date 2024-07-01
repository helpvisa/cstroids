#include "../structs.h"

#ifndef ASTEROID_H_
#define ASTEROID_H_

Asteroid *create_asteroid(Vector2 pos, Vector2 velocity, float size, float rot);
void insert_asteroid_at_beginning(struct AsteroidNode **head, Asteroid *roid);
void insert_asteroid_at_end(struct AsteroidNode **head, Asteroid *roid);
void remove_asteroid_from_list(struct AsteroidNode **head, struct AsteroidNode **ref);
void update_asteroid(struct AsteroidNode **ref);
void draw_asteroid(struct AsteroidNode *ref);
void update_asteroid_list(struct AsteroidNode **head);
void draw_asteroid_list(struct AsteroidNode *head);

#endif
