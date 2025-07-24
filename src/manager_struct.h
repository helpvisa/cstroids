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

#ifndef MANAGER_STRUCT_H
#define MANAGER_STRUCT_H
#include "region.h"
#include "structs.h"

/* define the parameters of your game manager */
struct GameManager {
    /* info about this manager */
    size_t region_size;
    int number_of_particles;
    int number_of_bullets;
    
    /* memory regions */
    struct Region *scratch_region;
    struct Region *general_region;
    struct Region *particle_region;
    struct Region *asteroid_region;
    struct Region *bullet_region;

    /* pools of objects */
    Particle *used_particles;
    Particle *free_particles;
    Asteroid *used_roids;
    Asteroid *free_roids;
    Bullet *used_bullets;
    Bullet *free_bullets;

    /* game globals, like players */
    Ship player_ship;
    int score;
};

#endif
