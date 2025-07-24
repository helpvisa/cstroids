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

#ifndef ASTEROID_H_
#define ASTEROID_H_
#include "../region.h"
#include "../structs.h"
#include "../manager.h"

Asteroid *create_asteroid(struct Region *region);
void set_asteroid(Asteroid *roid,
                  Vector2 pos, Vector2 velocity, float size, float rot);

void insert_asteroid_at_beginning(Asteroid **head, Asteroid *roid);
void insert_asteroid_at_end(Asteroid **head, Asteroid *roid);
void remove_asteroid_from_list(Asteroid **head, Asteroid *ref);

void update_asteroid(Asteroid *roid, struct GameManager *gm);
void draw_asteroid(Asteroid *roid);
void update_asteroid_list(Asteroid *head, struct GameManager *gm);
void clean_asteroid_list(Asteroid **head, Asteroid **deposit);
void draw_asteroid_list(Asteroid *head);

#endif
