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

#ifndef COLLIDE_H_
#define COLLIDE_H_

int collide_point(Vector2 p, Vector2 *o, int o_count, Vector2 o_offset);
int collide_polygons(Vector2 *o1, int o1_count, Vector2 o1_offset, Vector2 *o2,
                     int o2_count, Vector2 o2_offset);

#endif
