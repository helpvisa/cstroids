#include "../defs.h"
#include "../structs.h"
#include "../wrap_sdl/draw.h"
#include "../generic/collide.h"

extern struct AsteroidNode *asteroids_head;
extern struct ParticleNode *particles_head;
extern struct BulletNode *bullets_head;

extern float ratio;
extern Ship *player_ship;

Particle *create_particle(Vector2 pos, Vector2 velocity, int lifetime, Colour col, float size) {
    Particle *part = malloc(sizeof(Particle));
    part->pos = pos;
    part->velocity = velocity;
    part->lifetime = lifetime;
    part->life = lifetime;
    part->col = col;
    part->size = size;
    return part;
}

void insert_particle_at_beginning(struct ParticleNode **head, Particle *part) {
    struct ParticleNode *new_node = malloc(sizeof(struct ParticleNode));
    new_node->part = part;
    new_node->next = *head;
    *head = new_node;
}

void insert_particle_at_end(struct ParticleNode **head, Particle *part) {
    struct ParticleNode *new_node = malloc(sizeof(struct ParticleNode));
    new_node->part = part;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    // iterate toward final node to add to end of list
    struct ParticleNode *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void remove_particle_from_list(struct ParticleNode **head, struct ParticleNode **ref) {
    struct ParticleNode *current = *head, *prev;

    if (current != NULL && current->part == (*ref)->part) {
        *ref = current->next;
        *head = current->next;
        free(current->part);
        free(current);
        return;
    }

    while (current != NULL && current->part != (*ref)->part) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    prev->next = current->next;
    *ref = prev;
    free(current->part);
    free(current);
}

void update_particle(struct ParticleNode **ref) {
    (*ref)->part->pos.x += (*ref)->part->velocity.x;
    (*ref)->part->pos.y += (*ref)->part->velocity.y;
    // wrap part back across borders
    if ((*ref)->part->pos.x > DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 10) {
        (*ref)->part->pos.x = -10;
    } else if ((*ref)->part->pos.x < -10) {
        (*ref)->part->pos.x = DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 10;
    }
    if ((*ref)->part->pos.y > DEFAULT_SCREEN_HEIGHT + 10) {
        (*ref)->part->pos.y = -10;
    } else if ((*ref)->part->pos.y < -10) {
        (*ref)->part->pos.y = DEFAULT_SCREEN_HEIGHT + 10;
    }
    // friction
    (*ref)->part->velocity.x *= 0.96;
    (*ref)->part->velocity.y *= 0.96;
    (*ref)->part->velocity.x += 0.001;
    (*ref)->part->velocity.y += 0.001;
    // bump from ship, asteroids, bullets
    if (collide_point((*ref)->part->pos, player_ship->offsets, player_ship->offset_count, player_ship->pos)) {
        (*ref)->part->velocity.x += player_ship->velocity.x / 6;
        (*ref)->part->velocity.y += player_ship->velocity.y / 6;
    }
    struct AsteroidNode *curr_roid = asteroids_head;
    while (curr_roid != NULL) {
        if (collide_point((*ref)->part->pos, curr_roid->roid->offsets, curr_roid->roid->offset_count, curr_roid->roid->pos)) {
            (*ref)->part->velocity.x += ((*ref)->part->pos.x - curr_roid->roid->pos.x) / 20;
            (*ref)->part->velocity.y += ((*ref)->part->pos.y - curr_roid->roid->pos.y) / 20;
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
        if (collide_point((*ref)->part->pos, o, 4, curr_bullet->bullet->pos)) {
            (*ref)->part->velocity.x += curr_bullet->bullet->velocity.x / 6;
            (*ref)->part->velocity.y += curr_bullet->bullet->velocity.y / 6;
        }
        curr_bullet = curr_bullet->next;
    }
    // decay
    (*ref)->part->life -= 1;
    float decay = ((float)(*ref)->part->life / (*ref)->part->lifetime);
    /* (*ref)->part->size *= decay; */
    if ((*ref)->part->size > 2) {
        (*ref)->part->size -= 0.25;
    } else {
        (*ref)->part->size = 2;
        (*ref)->part->size *= decay;
    }
    if ((*ref)->part->col.a > 60) {
        (*ref)->part->col.a -= 1;
    }
    if ((*ref)->part->life < 0) {
        remove_particle_from_list(&particles_head, ref);
    }
}

void draw_particle(struct ParticleNode *ref) {
    Vector2 point = {ref->part->pos.x, ref->part->pos.y};
    render_point(point, ref->part->col, ref->part->size);
}

void update_particle_list(struct ParticleNode **head) {
    if (*head == NULL) {
        return;
    }

    // iterate through all particles in linked list
    struct ParticleNode *current = *head;
    while (current != NULL) {
        update_particle(&current);
        // a particle could have been removed; we must check again
        if (current != NULL) {
            current = current->next;
        }
    }
}

void draw_particle_list(struct ParticleNode *head) {
    if (head == NULL) {
        return;
    }

    struct ParticleNode *current = head;
    while (current != NULL) {
        draw_particle(current);
        current = current->next;
    }
}
