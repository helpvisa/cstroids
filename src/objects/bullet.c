#include "../defs.h"
#include "../structs.h"
#include "../rng.h"
#include "../wrap_sdl/draw.h"
#include "particle.h"
#include <math.h>

extern struct ParticleNode *particles_head;
extern struct BulletNode *bullets_head;
extern int bullet_count;

extern float ratio;

Bullet *create_bullet(Vector2 pos, Vector2 velocity, Colour col, int life) {
    Bullet *bullet = malloc(sizeof(Bullet));
    bullet->pos = pos;
    bullet->velocity = velocity;
    bullet->col = col;
    bullet->life = life;

    return bullet;
}

void insert_bullet_at_beginning(struct BulletNode **head, Bullet *bullet) {
    struct BulletNode *new_node = malloc(sizeof(struct BulletNode));
    new_node->bullet = bullet;
    new_node->next = *head;
    *head = new_node;
}

void insert_bullet_at_end(struct BulletNode **head, Bullet *bullet) {
    struct BulletNode *new_node = malloc(sizeof(struct BulletNode));
    new_node->bullet = bullet;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    // iterate toward final node and add to end of list
    struct BulletNode *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void remove_bullet_from_list(struct BulletNode **head, struct BulletNode **ref) {
    struct BulletNode *current = *head, *prev;

    if (current != NULL && current->bullet == (*ref)->bullet) {
        *ref = current->next;
        *head = current->next;
        free(current->bullet);
        free(current);
        return;
    }

    while (current != NULL && current->bullet != (*ref)->bullet) {
        prev = current;
        current = current->next;
    }

    // bullet not in linked list
    if (current == NULL) {
        return;
    }

    prev->next = current->next;
    *ref = prev;
    free(current->bullet);
    free(current);
}

void update_bullet(struct BulletNode **ref) {
    (*ref)->bullet->life -= 1;

    (*ref)->bullet->pos.x += (*ref)->bullet->velocity.x;
    (*ref)->bullet->pos.y += (*ref)->bullet->velocity.y;
    // wrap around borders
    if ((*ref)->bullet->pos.x > DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 10) {
        (*ref)->bullet->pos.x = -10;
    } else if ((*ref)->bullet->pos.x < -10) {
        (*ref)->bullet->pos.x = DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 10;
    }
    if ((*ref)->bullet->pos.y > DEFAULT_SCREEN_HEIGHT + 10) {
        (*ref)->bullet->pos.y = -10;
    } else if ((*ref)->bullet->pos.y < -10) {
        (*ref)->bullet->pos.y = DEFAULT_SCREEN_HEIGHT + 10;
    }
    // delete if life is out
    if ((*ref)->bullet->life < 0) {
        // spawn fan of particles
        for (float angle = 0; angle < 360; angle += 45) {
            float angle_rad = angle * (PI / 180);
            float s = sin(angle_rad);
            float c = cos(angle_rad);

            float x_rand = (float)rng(10, 0) / 10;
            float y_rand = (float)rng(10, 0) / 10;

            Vector2 part_origin = {(*ref)->bullet->pos.x, (*ref)->bullet->pos.y};
            Vector2 part_vel = {c + (x_rand - 0.5) / 2, s + (y_rand - 0.5) / 2};
            Colour col = {60 * y_rand, 200, 60 * x_rand, 255};
            Particle *new_part = create_particle(part_origin,
                                                 part_vel,
                                                 60 * (8 + x_rand + y_rand),
                                                 col,
                                                 4 + x_rand + y_rand);
            insert_particle_at_end(&particles_head, new_part);
        }
        // now delete
        remove_bullet_from_list(&bullets_head, ref);
        bullet_count -= 1;
    }
}

void draw_bullet(struct BulletNode *ref) {
    Vector2 trail = {ref->bullet->pos.x - ref->bullet->velocity.x,
                     ref->bullet->pos.y - ref->bullet->velocity.y};
    render_line(ref->bullet->pos, trail, ref->bullet->col);
}

void update_bullet_list(struct BulletNode **head) {
    if (*head == NULL) {
        return;
    }

    struct BulletNode *current = *head;
    while (current != NULL) {
        update_bullet(&current);
        if (current != NULL) {
            current = current->next;
        }
    }
}

void draw_bullet_list(struct BulletNode *head) {
    if (head == NULL) {
        return;
    }

    struct BulletNode *current = head;
    while (current != NULL) {
        draw_bullet(current);
        current = current->next;
    }
}
