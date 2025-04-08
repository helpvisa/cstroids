#ifndef GAME_H_
#define GAME_H_

#include "structs.h"
#include "manager.h"

void reset_game(struct GameManager *gm,
                Ship *player_ship, Vector2 *ship_offsets, int *player_state,
                Vector2 init_pos);

#endif
