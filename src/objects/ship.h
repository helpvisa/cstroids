#include "../structs.h"
#include "../manager.h"

#ifndef SHIP_H_
#define SHIP_H_

Ship *init_ship(Vector2 pos, Vector2 *offsets, int offset_count);
void update_ship(Ship *ship, struct GameManager *gm);
void draw_ship(Ship *ship);

#endif
