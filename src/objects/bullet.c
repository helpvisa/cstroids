#include "../defs.h"
#include "../structs.h"
#include "../rng.h"
#include "../wrap_sdl/draw.h"
#include "particle.h"
#include "asteroid.h"
#include "../generic/collide.h"
#include "../helpers/particle-helpers.h"
#include "../helpers/asteroid-helpers.h"

extern struct ParticleNode *particles_head;
extern struct AsteroidNode *asteroids_head;
extern struct BulletNode *bullets_head;
extern int bullet_count;

extern float ratio;
extern const Vector2 zero_vector;

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
        Colour fan_part_col = {60, 200, 60, 255};
        Vector2 fan_part_pos = {(*ref)->bullet->pos.x, (*ref)->bullet->pos.y};
        create_particle_fan(&particles_head, 0.79, fan_part_pos, fan_part_col, 60, 4, 1, 55);
        // now delete
        remove_bullet_from_list(&bullets_head, ref);
        bullet_count -= 1;
    } else {
        // delete if hitting asteroid
        struct AsteroidNode *curr_roid = asteroids_head;
        while (curr_roid != NULL) {
            // check strip to more closely match visual
            /* Vector2 vel_point = {(*ref)->bullet->pos.x - (*ref)->bullet->velocity.x, */
            /*                      (*ref)->bullet->pos.y - (*ref)->bullet->velocity.y}; */
            /* Vector2 bullet_offsets[2] = {(*ref)->bullet->pos, vel_point}; */
            Vector2 b1 = {-10, -10};
            Vector2 b2 = { 10, -10};
            Vector2 b3 = { 10,  10};
            Vector2 b4 = { 10,  10};
            Vector2 o[4] = {b1, b2, b3, b4};
            /* if (collide_polygons(bullet_offsets, 2, zero_vector, curr_roid->roid->offsets, curr_roid->roid->offset_count, curr_roid->roid->pos)) { */
            if (collide_polygons(o, 4, (*ref)->bullet->pos, curr_roid->roid->offsets, curr_roid->roid->offset_count, curr_roid->roid->pos)) {
                bullet_count -= 1;
                // spawn child asteroids
                if (curr_roid->roid->size > 0.8) {
                    Vector2 bullet_influence = {(*ref)->bullet->velocity.x / 10, (*ref)->bullet->velocity.y / 10};
                    spawn_child_asteroids(&asteroids_head, curr_roid->roid, bullet_influence, 0.4, 2);
                }
                // spawn fan of particles (asteroid)
                Colour roid_part_col = {200, 60, 200, 255};
                Vector2 roid_part_pos = {curr_roid->roid->pos.x, curr_roid->roid->pos.y};
                create_particle_fan(&particles_head, 0.26, roid_part_pos, roid_part_col, 60, 4, 1.6, 20);
                // spawn fan of particles (bullet)
                Colour bul_part_col = {60, 200, 60, 255};
                Vector2 bul_part_pos = {(*ref)->bullet->pos.x, (*ref)->bullet->pos.y};
                create_particle_fan(&particles_head, 2.09, bul_part_pos, bul_part_col, 60, 4, 1, 55);

                // remove bullet and asteroid from update lists
                remove_asteroid_from_list(&asteroids_head, &curr_roid);
                remove_bullet_from_list(&bullets_head, ref);
                break;
            }
            curr_roid = curr_roid->next;
        }
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
