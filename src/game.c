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
