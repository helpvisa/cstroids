/*
   Copyright 2025 Daniel Brackenbury

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <stdio.h>
#include <math.h>
#include "../defs.h"
#include "../structs.h"
#include "../rng.h"
#include "../wrap_sdl/draw.h"
#include "../region.h"
#include "../manager.h"
#include "../helpers/asteroid-helpers.h"
#include "../helpers/particle-helpers.h"

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

Asteroid *create_asteroid(struct Region *region) {
    Asteroid *roid = region_alloc(region, sizeof(*roid));
    roid->offsets = region_alloc(region, sizeof(Vector2) * 8);
    roid->offset_count = 8;

    return roid;
}

void set_asteroid(Asteroid *roid,
                  Vector2 pos, Vector2 velocity, float size, float rot) {
    if (roid) {
        Vector2 zero = {0};

        roid->pos = pos;
        roid->velocity = velocity;
        roid->size = size;   // float multiplier for size
        roid->rotation_speed = rot;
        roid->was_hit = 0;
        roid->hit_influence = zero;
        roid->next = NULL;

        // slightly randomize offsets for visual variation
        for (int i = 0; i < roid->offset_count; i++) {
            float rand_x = ((float)rng(10, 0) / 10 - 0.5) * 16;
            float rand_y = ((float)rng(10, 0) / 10 - 0.5) * 16;
            roid->offsets[i].x = roid_offsets[i].x + rand_x;
            roid->offsets[i].y = roid_offsets[i].y + rand_y;
            // apply size multiplier
            roid->offsets[i].x *= roid->size;
            roid->offsets[i].y *= roid->size;
        }
    }
}

void insert_asteroid_at_beginning(Asteroid **head, Asteroid *roid) {
    roid->next = *head;
    *head = roid;
}

void insert_asteroid_at_end(Asteroid **head, Asteroid *roid) {
    roid->next = NULL;

    if (!*head) {
        *head = roid;
        return;
    }

    // iterate toward final node and add to end of list
    Asteroid *current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = roid;
}

void remove_asteroid_from_list(Asteroid **head, Asteroid *ref) {
    Asteroid *current = *head, *prev;

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

void update_asteroid(Asteroid *roid, struct GameManager *gm) {
    roid->pos.x += roid->velocity.x;
    roid->pos.y += roid->velocity.y;
    // wrap roid around borders
    if (roid->pos.x > DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 20) {
        roid->pos.x = -20;
    } else if (roid->pos.x < -20) {
        roid->pos.x = DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 20;
    }
    if (roid->pos.y > DEFAULT_SCREEN_HEIGHT + 20) {
        roid->pos.y = -20;
    } else if (roid->pos.y < -20) {
        roid->pos.y = DEFAULT_SCREEN_HEIGHT + 20;
    }
    // rotate roid
    float rotation_angle = roid->rotation_speed * (PI / 180);
    float s = sin(rotation_angle);
    float c = cos(rotation_angle);
    for (int i = 0; i < roid->offset_count; i++) {
        float new_x = c * roid->offsets[i].x - s * roid->offsets[i].y;
        float new_y = s * roid->offsets[i].x + c * roid->offsets[i].y;
        roid->offsets[i].x = new_x;
        roid->offsets[i].y = new_y;
    }
    // split roid
    /* TODO: check here for a bullet collision and not in bullet,
       will need to create new function to check poly against poly */
    if (roid->was_hit) {
        // spawn fan of particles (asteroid)
        Colour roid_part_col = {200, 60, 200, 255};
        create_particle_fan(2 * PI / (roid->size * 100),
                            roid->hit_pos, roid_part_col, 60, 4, 10, 20,
                            gm);
        if (roid->size > 0.8) {
            spawn_child_asteroids(gm, roid, 0.5, 2);
        }
        // increase the score
        request_score_change(gm, BASE_SCORE * (2 - roid->size));
    }
}

void draw_asteroid(Asteroid *roid) {
    Vector2 points[roid->offset_count + 1];
    for (int i = 0; i < roid->offset_count; i++) {
        Vector2 global_point_position = {roid->pos.x + roid->offsets[i].x,
                                         roid->pos.y + roid->offsets[i].y};
        points[i] = global_point_position;
    }
    // duplicate first point to close the poly
    points[roid->offset_count] = points[0];

    Colour col = {255, 100, 255, 255};
    render_polygon(points, roid->offset_count + 1, col);
}

void update_asteroid_list(Asteroid *head, struct GameManager *gm) {
    Asteroid *current = head;

    while (current) {
        update_asteroid(current, gm);
        current = current->next;
    }
}

void clean_asteroid_list(Asteroid **head, Asteroid **deposit) {
    Asteroid *current = *head;

    while (current) {
        if (current->was_hit) {
            remove_asteroid_from_list(head, current);
            insert_asteroid_at_end(deposit, current);
        }
        current = current->next;
    }
}

void draw_asteroid_list(Asteroid *head) {
    Asteroid *current = head;
    while (current) {
        draw_asteroid(current);
        current = current->next;
    }
}
