#include "../defs.h"
#include "../structs.h"
#include "../rng.h"
#include "../wrap_sdl/draw.h"
#include "particle.h"
#include "asteroid.h"
#include "../generic/collide.h"
#include "../helpers/particle-helpers.h"
#include "../helpers/asteroid-helpers.h"
#include "../manager.h"

extern float ratio;
extern const Vector2 zero_vector;

Bullet *create_bullet(struct Region *region) {
    Bullet *bullet = region_alloc(region, sizeof(*bullet));

    return bullet;
}

void set_bullet(Bullet *bullet,
                Vector2 pos, Vector2 velocity, Colour col, int life) {
    bullet->pos = pos;
    bullet->velocity = velocity;
    bullet->col = col;
    bullet->life = life;

    bullet->next = NULL;
}

void insert_bullet_at_beginning(Bullet **head, Bullet *bullet) {
    bullet->next = *head;
    *head = bullet;
}

void insert_bullet_at_end(Bullet **head, Bullet *bullet) {
    bullet->next = NULL;

    if (!*head) {
        *head = bullet;
        return;
    }

    // iterate toward final node and add to end of list
    Bullet *current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = bullet;
}

void remove_bullet_from_list(Bullet **head, Bullet *ref) {
    Bullet *current = *head, *prev;

    if (!ref) {
        return;
    }

    if (*head && *head == ref) {
        *head = (*head)->next;
        return;
    }

    while (current && current != ref) {
        prev = current;
        current = current->next;
    }

    if (current) {
        prev->next = current->next;
    }
}

void update_bullet(Bullet *bullet, struct GameManager *gm) {
    bullet->life -= 1;

    bullet->pos.x += bullet->velocity.x;
    bullet->pos.y += bullet->velocity.y;
    // wrap around borders
    if (bullet->pos.x > DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 10) {
        bullet->pos.x = -10;
    } else if (bullet->pos.x < -10) {
        bullet->pos.x = DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 10;
    }
    if (bullet->pos.y > DEFAULT_SCREEN_HEIGHT + 10) {
        bullet->pos.y = -10;
    } else if (bullet->pos.y < -10) {
        bullet->pos.y = DEFAULT_SCREEN_HEIGHT + 10;
    }
    // delete if hitting asteroid
    /* struct AsteroidNode *curr_roid = asteroids_head; */
    /* while (curr_roid != NULL) { */
    /*     // check strip to more closely match visual */
    /*     /\* Vector2 vel_point = {bullet->pos.x - bullet->velocity.x, *\/ */
    /*     /\*                      bullet->pos.y - bullet->velocity.y}; *\/ */
    /*     /\* Vector2 bullet_offsets[2] = {bullet->pos, vel_point}; *\/ */
    /*     Vector2 b1 = {-10, -10}; */
    /*     Vector2 b2 = { 10, -10}; */
    /*     Vector2 b3 = { 10,  10}; */
    /*     Vector2 b4 = { 10,  10}; */
    /*     Vector2 o[4] = {b1, b2, b3, b4}; */
    /*     /\* if (collide_polygons(bullet_offsets, 2, zero_vector, curr_roid->roid->offsets, curr_roid->roid->offset_count, curr_roid->roid->pos)) { *\/ */
    /*     if (collide_polygons(o, 4, bullet->pos, curr_roid->roid->offsets, curr_roid->roid->offset_count, curr_roid->roid->pos)) { */
    /*         bullet_count -= 1; */
    /*         // spawn child asteroids */
    /*         if (curr_roid->roid->size > 0.8) { */
    /*             Vector2 bullet_influence = {bullet->velocity.x / 10, bullet->velocity.y / 10}; */
    /*             spawn_child_asteroids(&asteroids_head, curr_roid->roid, bullet_influence, 0.4, 2); */
    /*         } */
    /*         // spawn fan of particles (asteroid) */
    /*         Colour roid_part_col = {200, 60, 200, 255}; */
    /*         Vector2 roid_part_pos = {curr_roid->roid->pos.x, curr_roid->roid->pos.y}; */
    /*         /\* create_particle_fan(&particles_head, 0.26, roid_part_pos, roid_part_col, 60, 4, 1.6, 20); *\/ */
    /*         // spawn fan of particles (bullet) */
    /*         Colour bul_part_col = {60, 200, 60, 255}; */
    /*         Vector2 bul_part_pos = {bullet->pos.x, bullet->pos.y}; */
    /*         /\* create_particle_fan(&particles_head, 2.09, bul_part_pos, bul_part_col, 60, 4, 1, 55); *\/ */

    /*         // remove bullet and asteroid from update lists */
    /*         remove_asteroid_from_list(&asteroids_head, &curr_roid); */
    /*         remove_bullet_from_list(&bullets_head, ref); */
    /*         break; */
    /*     } */
    /*     curr_roid = curr_roid->next; */
    /* } */
}

void draw_bullet(Bullet *bullet) {
    Vector2 trail = {bullet->pos.x - bullet->velocity.x,
                     bullet->pos.y - bullet->velocity.y};
    render_line(bullet->pos, trail, bullet->col);
}

void update_bullet_list(Bullet *head, struct GameManager *gm) {
    Bullet *current = head;
    while (current) {
        update_bullet(current, gm);
        current = current->next;
    }
}

void clean_bullet_list(Bullet **head, Bullet **deposit) {
    Bullet *current = *head;

    while (current) {
        if (current->life < 0) {
            // spawn fan of particles
            Colour fan_part_col = {60, 200, 60, 255};
            Vector2 fan_part_pos = {current->pos.x, current->pos.y};
            /* create_particle_fan(&particles_head, 0.79, fan_part_pos, fan_part_col, 60, 4, 1, 55); */
            // now delete
            remove_bullet_from_list(head, current);
            insert_bullet_at_end(deposit, current);
        }
        current = current->next;
    }
}

void draw_bullet_list(Bullet *head) {
    if (head == NULL) {
        return;
    }

    Bullet *current = head;
    while (current) {
        draw_bullet(current);
        current = current->next;
    }
}
