#include "../structs.h"

#ifndef DRAW_H_
#define DRAW_H_

void prepare_scene(int r, int g, int b, int a);
void present_scene();
void update_window();
void render_point(Vector2 point, Colour col, float size);
void render_line(Vector2 p1, Vector2 p2, Colour col);
void render_polygon(Vector2 *vectors, int count, Colour col);

#endif
