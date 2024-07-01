#include "../defs.h"
#include "../structs.h"
#include "../wrap_sdl/draw.h"

extern struct ParticleNode *particles_head;
extern float ratio;

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
    (*ref)->part->velocity.x *= 0.95;
    (*ref)->part->velocity.y *= 0.95;
    // decay
    (*ref)->part->life -= 1;
    float decay = ((float)(*ref)->part->life / (*ref)->part->lifetime);
    (*ref)->part->size *= decay;
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
