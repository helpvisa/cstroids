#include "../structs.h"

#ifndef BULLET_H_
#define BULLET_H_

Bullet *create_bullet(Vector2 pos, Vector2 velocity, Colour col, int life);
void insert_bullet_at_beginning(struct BulletNode **head, Bullet *bullet);
void insert_bullet_at_end(struct BulletNode **head, Bullet *bullet);
void remove_bullet_from_list(struct BulletNode **head, struct BulletNode **ref);
void update_bullet(struct BulletNode **ref);
void draw_bullet(struct BulletNode *ref);
void update_bullet_list(struct BulletNode **head);
void draw_bullet_list(struct BulletNode *head);

#endif
