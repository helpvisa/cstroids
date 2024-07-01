#include "../defs.h"
#include "../structs.h"
#include "../rng.h"
#include "../wrap_sdl/draw.h"
#include <math.h>

extern struct AsteroidNode *asteroids_head;
extern float ratio;

// define a "standard asteroid offset look"
Vector2 roid_offsets[] = {
    {-20, 0},
    {-15, 10},
    {0, 20},
    {15, 10},
    {20, 0},
    {15, -10},
    {0, -20},
    {-15, -10}
};

Asteroid *create_asteroid(Vector2 pos, Vector2 velocity, float size, float rot) {
    Asteroid *roid = malloc(sizeof(Asteroid));
    roid->pos = pos;
    roid->velocity = velocity;
    roid->size = size;   // float multiplier for size
    roid->rotation_speed = rot;
    roid->offsets = roid_offsets;
    roid->offset_count = 8;

    // slightly randomize offsets for visual variation
    for (int i = 0; i < roid->offset_count; i++) {
        float rand_x = ((float)rng(10, 0) / 10 - 0.5) * 8;
        float rand_y = ((float)rng(10, 0) / 10 - 0.5) * 8;
        roid->offsets[i].x += rand_x;
        roid->offsets[i].y += rand_y;
        // apply size multiplier
        roid->offsets[i].x *= roid->size;
        roid->offsets[i].y *= roid->size;
    }

    return roid;
}

void insert_asteroid_at_beginning(struct AsteroidNode **head, Asteroid *roid) {
    struct AsteroidNode *new_node = malloc(sizeof(struct AsteroidNode));
    new_node->roid = roid;
    new_node->next = *head;
    *head = new_node;
}

void insert_asteroid_at_end(struct AsteroidNode **head, Asteroid *roid) {
    struct AsteroidNode *new_node = malloc(sizeof(struct AsteroidNode));
    new_node->roid = roid;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    // iterate toward final node and add to end of list
    struct AsteroidNode *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void remove_asteroid_from_list(struct AsteroidNode **head, struct AsteroidNode **ref) {
    struct AsteroidNode *current = *head, *prev;

    if (current != NULL && current->roid == (*ref)->roid) {
        *ref = current->next;
        *head = current->next;
        free(current->roid);
        free(current);
        return;
    }

    while (current != NULL && current->roid != (*ref)->roid) {
        prev = current;
        current = current->next;
    }

    // asteroid is not in the linked list
    if (current == NULL) {
        return;
    }

    prev->next = current->next;
    *ref = prev;
    free(current->roid);
    free(current);
}

void update_asteroid(struct AsteroidNode **ref) {
    (*ref)->roid->pos.x += (*ref)->roid->velocity.x;
    (*ref)->roid->pos.y += (*ref)->roid->velocity.y;
    // wrap roid around borders
    if ((*ref)->roid->pos.x > DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 20) {
        (*ref)->roid->pos.x = -20;
    } else if ((*ref)->roid->pos.x < -20) {
        (*ref)->roid->pos.x = DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 20;
    }
    if ((*ref)->roid->pos.y > DEFAULT_SCREEN_HEIGHT + 20) {
        (*ref)->roid->pos.y = -20;
    } else if ((*ref)->roid->pos.y < -20) {
        (*ref)->roid->pos.y = DEFAULT_SCREEN_HEIGHT + 20;
    }
    // rotate roid
    float rotation_angle = (*ref)->roid->rotation_speed * (PI / 180);
    float s = sin(rotation_angle);
    float c = cos(rotation_angle);
    for (int i = 0; i < (*ref)->roid->offset_count; i++) {
        float new_x = c * (*ref)->roid->offsets[i].x - s * (*ref)->roid->offsets[i].y;
        float new_y = s * (*ref)->roid->offsets[i].x + c * (*ref)->roid->offsets[i].y;
        (*ref)->roid->offsets[i].x = new_x;
        (*ref)->roid->offsets[i].y = new_y;
    }
}

void draw_asteroid(struct AsteroidNode *ref) {
    Vector2 points[ref->roid->offset_count + 1];
    for (int i = 0; i < ref->roid->offset_count; i++) {
        Vector2 global_point_position = {ref->roid->pos.x + ref->roid->offsets[i].x,
                                         ref->roid->pos.y + ref->roid->offsets[i].y};
        points[i] = global_point_position;
    }
    // duplicate first point to close the poly
    points[ref->roid->offset_count] = points[0];

    Colour col = {255, 100, 255, 255};
    render_polygon(points, ref->roid->offset_count + 1, col);
}

void update_asteroid_list(struct AsteroidNode **head) {
    if (*head == NULL) {
        return;
    }

    // iterate thru linked list
    struct AsteroidNode *current = *head;
    while (current != NULL) {
        update_asteroid(&current);
        current = current->next;
    }
}

void draw_asteroid_list(struct AsteroidNode *head) {
    if (head == NULL) {
        return;
    }

    struct AsteroidNode *current = head;
    while (current != NULL) {
        draw_asteroid(current);
        current = current->next;
    }
}
