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
