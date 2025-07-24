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
