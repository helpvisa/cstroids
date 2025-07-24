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

#ifndef SHIP_H_
#define SHIP_H_

#include "../structs.h"
#include "../manager.h"
#include "../region.h"

Ship *create_ship(struct Region *region);
void set_ship(Ship *ship, Vector2 pos, Vector2 *offsets, int offset_count);
void rotate_ship(Ship *ship, float amount_to_rotate);

void update_ship(Ship *ship, struct GameManager *gm);
void draw_ship(Ship *ship);

#endif
