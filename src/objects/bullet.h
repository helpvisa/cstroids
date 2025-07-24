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

#ifndef BULLET_H_
#define BULLET_H_

#include "../structs.h"
#include "../region.h"
#include "../manager.h"

Bullet *create_bullet(struct Region *region);
void set_bullet(Bullet *bullet,
                Vector2 pos, Vector2 velocity, Colour col, int life);

void insert_bullet_at_beginning(Bullet **head, Bullet *bullet);
void insert_bullet_at_end(Bullet **head, Bullet *bullet);
void remove_bullet_from_list(Bullet **head, Bullet *ref);

void update_bullet(Bullet *bullet, struct GameManager *gm);
void draw_bullet(Bullet *bullet);
void update_bullet_list(Bullet *head, struct GameManager *gm);
void clean_bullet_list(Bullet **head, Bullet **deposit);
void draw_bullet_list(Bullet *head);

#endif
