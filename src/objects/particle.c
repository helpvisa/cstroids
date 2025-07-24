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

#include <stdlib.h>

#include "../defs.h"
#include "../structs.h"
#include "../wrap_sdl/draw.h"
#include "../generic/collide.h"
#include "../region.h"
#include "../manager.h"

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

void update_particle(Particle *part, struct GameManager *gm) {
    if (part->life > 0) {
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
        // check if we collided into an asteroid
        Asteroid *roid_col = request_roid_collision_point(gm, part->pos);
        if (roid_col) {
            part->velocity.x += (part->pos.x - roid_col->pos.x) / 20;
            part->velocity.y += (part->pos.y - roid_col->pos.y) / 20;
        }

        // TODO: bullets affect our trajectory
        Bullet *bullet_col = request_bullet_collision_point(gm, part->pos, 6);
        if (bullet_col) {
            part->velocity.x += bullet_col->velocity.x / 6;
            part->velocity.y += bullet_col->velocity.y / 6;
        }
        // decay
        part->life -= 1;
        float decay = ((float)part->life / part->lifetime);
        if (decay < 0) {
            decay = 0;
        }
        if (part->size > 1) {
            part->size -= 0.25;
        } else {
            part->size = 1;
            /* part->size = 1 * decay; */
        }
        if (part->col.a > 100) {
            part->col.a -= 1;
        } else if (part->life < 100) {
            part->col.a = part->life;
        }
    }
}

void draw_particle(Particle *part) {
    if (part->life > 0) {
        Vector2 point = {part->pos.x, part->pos.y};
        render_point(point, part->col, part->size);
    }
}

void update_particle_list(Particle *head, struct GameManager *gm) {
    Particle *current = head;
    while (current) {
        update_particle(current, gm);
        current = current->next;
    }
}

void clean_particle_list(Particle **head, Particle **deposit) {
    Particle *current = *head;

    while (current) {
        if (current->life < 1) {
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
