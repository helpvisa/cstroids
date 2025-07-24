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

#include "defs.h"
#include "structs.h"
#include "objects/ship.h"
#include "region.h"

// rendering
App app = {NULL, NULL};
float zoom_x = 1;
float zoom_y = 1;
float ratio = DEFAULT_RATIO;
int screen_width = DEFAULT_SCREEN_WIDTH;
int screen_height = DEFAULT_SCREEN_HEIGHT;

// linked lists
struct ParticleNode *particles_head = NULL;
struct AsteroidNode *asteroids_head = NULL;
struct BulletNode *bullets_head = NULL;

// regions
struct Region *particles_region = NULL;

// game state
enum game_state {TITLE, ACTIVE, OVER};

// player
Ship *player_ship = NULL;
int player_is_alive = 1;
int bullet_count = 0;

// math and vectors
const Vector2 zero_vector = {0, 0};
