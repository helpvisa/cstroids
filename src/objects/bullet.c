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
    if (bullet->life > 0) {
        bullet->pos.x += bullet->velocity.x;
        bullet->pos.y += bullet->velocity.y;
        // wrap around borders
        if (bullet->pos.x > DEFAULT_SCREEN_WIDTH * (ratio/DEFAULT_RATIO) + 10) {
            bullet->pos.x = -10;
        } else if (bullet->pos.x < -10) {
            bullet->pos.x = DEFAULT_SCREEN_WIDTH * (ratio/DEFAULT_RATIO) + 10;
        }
        if (bullet->pos.y > DEFAULT_SCREEN_HEIGHT + 10) {
            bullet->pos.y = -10;
        } else if (bullet->pos.y < -10) {
            bullet->pos.y = DEFAULT_SCREEN_HEIGHT + 10;
        }
        // delete if hitting asteroid
        Asteroid *roid_col = request_roid_collision_point(gm, bullet->pos);
        // spawn child asteroids
        if (roid_col) {
            /* bullet is destroyed; set life to 0 */
            bullet->life = 0;
            roid_col->was_hit = 1;
            Vector2 influence = {bullet->velocity.x / 10,
                                 bullet->velocity.y / 10};
            roid_col->hit_influence = influence;
            roid_col->hit_pos = bullet->pos;
        }
    } else {
        Colour fan_part_col = {60, 200, 60, 255};
        Vector2 fan_part_pos = {bullet->pos.x, bullet->pos.y};
        create_particle_fan(2 * PI / 6,
                            fan_part_pos, fan_part_col, 60, 4, 1, 55, gm);
    }
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
        if (current->life < 1) {
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
