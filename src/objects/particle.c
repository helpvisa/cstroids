#include "../defs.h"
#include "../structs.h"
#include "../wrap_sdl/draw.h"

extern float ratio;

Particle *create_particle(Vector2 pos, Vector2 velocity, int lifetime, Colour col) {
    Particle *part = malloc(sizeof(Particle));
    part->pos = pos;
    part->velocity = velocity;
    part->lifetime = lifetime;
    part->life = lifetime;
    part->col = col;
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
    new_node->next= NULL;

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

void update_particle(Particle *part) {
    part->pos.x += part->velocity.x;
    part->pos.y += part->velocity.y;
    // wrap ship back across borders
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
    part->velocity.x *= 0.98;
    part->velocity.y *= 0.98;
    // decay
    part->life -= 1;
    part->col.a *= ((float)part->life / part->lifetime);
}

void draw_particle(Particle *part) {
    Vector2 point = {part->pos.x, part->pos.y};
    render_point(point, part->col);
}

void update_particle_list(struct ParticleNode **head) {
    if (*head == NULL || (*head)->part == NULL) {
        return;
    }

    // update head
    update_particle((*head)->part);

    // iterate through all particles in linked list
    struct ParticleNode *current = *head;
    while (current->next != NULL) {
        current = current->next;
        update_particle(current->part);
    }
}

void draw_particle_list(struct ParticleNode **head) {
    if (*head == NULL || (*head)->part == NULL) {
        return;
    }

    draw_particle((*head)->part);

    struct ParticleNode *current = *head;
    while (current->next != NULL) {
        current = current->next;
        draw_particle(current->part);
    }
}
