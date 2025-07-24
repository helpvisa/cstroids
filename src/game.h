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

#ifndef GAME_H_
#define GAME_H_

#include "structs.h"
#include "manager.h"

void reset_game(struct GameManager *gm,
                Ship *player_ship, Vector2 *ship_offsets, int *player_state,
                Vector2 init_pos);

#endif
