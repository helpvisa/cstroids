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

#include "manager_struct.h"
#include "region.h"

struct GameManager gm_initialize(size_t region_size);
void gm_init_all(struct GameManager *gm,
                 int number_of_particles,
                 int number_of_bullets);
void gm_reset(struct GameManager *gm);
void gm_update_all(struct GameManager *gm);
void gm_draw_all(struct GameManager gm);

void request_new_particle(struct GameManager *gm,
                          Vector2 pos, Vector2 velocity,
                          int lifetime, Colour col, float size);
void request_new_asteroid(struct GameManager *gm,
                          Vector2 pos, Vector2 velocity,
                          float size, float rot);
void request_new_bullet(struct GameManager *gm,
                        Vector2 pos, Vector2 velocity, Colour col, int life);

Asteroid *request_roid_collision_point(struct GameManager *gm, Vector2 point);
Asteroid *request_roid_collision_poly(struct GameManager *gm,
                                      Vector2 *offsets, int offset_count,
                                      Vector2 position);
Bullet *request_bullet_collision_point(struct GameManager *gm,
                                       Vector2 point, float bullet_size);

void request_score_change(struct GameManager *gm, int change_by);
