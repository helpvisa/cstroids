#include <stdlib.h>

#include "../defs.h"
#include "../structs.h"
#include "../wrap_sdl/draw.h"
#include "../generic/collide.h"
#include "../region.h"

extern struct AsteroidNode *asteroids_head;
extern struct ParticleNode *particles_head;
extern struct BulletNode *bullets_head;

extern float ratio;
extern Ship *player_ship;

Particle *create_particle(struct Region *region) {
    Particle *part = region_alloc(region, sizeof(*part));
    return part;
}

void set_particle(Particle *part,
                  Vector2 pos, Vector2 velocity,
                  int lifetime, Colour col, float size) {
    if (part) {
        part->pos = pos;
        part->velocity = velocity;
        part->lifetime = lifetime;
        part->life = lifetime;
        part->col = col;
        part->size = size;
        part->next = NULL;
    }
}

void insert_particle_at_beginning(Particle **head, Particle *part) {
    part->next = *head;
    *head = part;
}

void insert_particle_at_end(Particle **head, Particle *part) {
    part->next = NULL;
    
    if (!*head) {
        *head = part;
        return;
    }

    // iterate toward final node to add to end of list
    Particle *current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = part;
}

void remove_particle_from_list(Particle **head, Particle *ref) {
    Particle *current = *head, *prev;

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

void update_particle(Particle *part) {
    part->pos.x += part->velocity.x;
    part->pos.y += part->velocity.y;
    // wrap part back across borders
    if (part->pos.x > DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 10) {
        part->pos.x = -10;
    } else if (part->pos.x < -10) {
        part->pos.x = DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 10;
    }
    if (part->pos.y > DEFAULT_SCREEN_HEIGHT + 10) {
        part->pos.y = -10;
    } else if (part->pos.y < -10) {
        part->pos.y = DEFAULT_SCREEN_HEIGHT + 10;
    }
    // friction
    part->velocity.x *= 0.96;
    part->velocity.y *= 0.96;
    part->velocity.x += 0.001;
    part->velocity.y += 0.001;
    // bump from ship, asteroids, bullets
    if (collide_point(part->pos,
                      player_ship->offsets,
                      player_ship->offset_count,
                      player_ship->pos)) {
        part->velocity.x += player_ship->velocity.x / 6;
        part->velocity.y += player_ship->velocity.y / 6;
    }
    struct AsteroidNode *curr_roid = asteroids_head;
    while (curr_roid != NULL) {
        if (collide_point(part->pos,
                          curr_roid->roid->offsets,
                          curr_roid->roid->offset_count,
                          curr_roid->roid->pos)) {
            part->velocity.x += (part->pos.x - curr_roid->roid->pos.x) / 20;
            part->velocity.y += (part->pos.y - curr_roid->roid->pos.y) / 20;
        }
        curr_roid = curr_roid->next;
    }
    struct BulletNode *curr_bullet = bullets_head;
    while (curr_bullet != NULL) {
        Vector2 b1 = {-6, -6};
        Vector2 b2 = { 6, -6};
        Vector2 b3 = { 6,  6};
        Vector2 b4 = { 6,  6};
        Vector2 o[4] = {b1, b2, b3, b4};
        if (collide_point(part->pos, o, 4, curr_bullet->bullet->pos)) {
            part->velocity.x += curr_bullet->bullet->velocity.x / 6;
            part->velocity.y += curr_bullet->bullet->velocity.y / 6;
        }
        curr_bullet = curr_bullet->next;
    }
    // decay
    part->life -= 1;
    float decay = ((float)part->life / part->lifetime);
    /* part->size *= decay; */
    if (part->size > 2) {
        part->size -= 0.25;
    } else {
        part->size = 2;
        part->size *= decay;
    }
    if (part->col.a > 60) {
        part->col.a -= 1;
    }
}

void draw_particle(Particle *part) {
    Vector2 point = {part->pos.x, part->pos.y};
    render_point(point, part->col, part->size);
}

void update_particle_list(Particle *head) {
    Particle *current = head;
    while (current) {
        update_particle(current);
        current = current->next;
    }
}

void clean_particle_list(Particle **head, Particle **deposit) {
    Particle *current = *head;

    while (current) {
        if (current->life <= 0) {
            remove_particle_from_list(head, current);
            insert_particle_at_end(deposit, current);
        }
        current = current->next;
    }
}

void draw_particle_list(Particle *head) {
    if (head == NULL) {
        return;
    }

    Particle *current = head;
    while (current) {
        draw_particle(current);
        current = current->next;
    }
}
