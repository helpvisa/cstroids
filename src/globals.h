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

#ifndef GLOBALS_H_
#define GLOBALS_H_
#include "structs.h"

// rendering
extern App app;
extern float zoom_x;
extern float zoom_y;
extern float ratio;
extern int screen_width;
extern int screen_height;

// linked lists
extern struct ParticleNode *particles_head;
extern struct AsteroidNode *asteroids_head;
extern struct BulletNode *bullets_head;

// regions
extern struct Region *particles_region;

// player
extern Ship *player_ship;
extern int player_is_alive;
extern int bullet_count;

// math and vectors
extern const Vector2 zero_vector;

#endif
