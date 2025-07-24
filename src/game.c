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
#include "region.h"
#include "manager.h"
#include "objects/ship.h"
#include "objects/asteroid.h"

void reset_game(struct GameManager *gm,
                Ship *player_ship, Vector2 *ship_offsets, int *player_state,
                Vector2 init_pos) {
    /* reset the game manager */
    gm_reset(gm);
    /* reset the ship */
    rotate_ship(player_ship, -player_ship->angle);
    set_ship(player_ship, init_pos, player_ship->offsets, 5);
    /* re-alive the player */
    *player_state = 1;
}
