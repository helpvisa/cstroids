#include "../structs.h"

#ifndef COLLIDE_H_
#define COLLIDE_H_

int collide_point(Vector2 p, Vector2 *o, int o_count, Vector2 o_offset);
int collide_polygons(Vector2 *o1, int o1_count, Vector2 o1_offset, Vector2 *o2,
                     int o2_count, Vector2 o2_offset);

#endif
