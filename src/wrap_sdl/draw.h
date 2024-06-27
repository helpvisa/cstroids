#include "../structs.h"

#ifndef DRAW_H_
#define DRAW_H_

void prepare_scene(int r, int g, int b, int a);
void present_scene();
void render_line(int x1, int y1, int x2, int y2, Colour col);
void render_polygon(Vector2 *vectors, int count, Colour col);

#endif
