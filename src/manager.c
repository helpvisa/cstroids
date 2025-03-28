#include <stdlib.h>

#include "manager_struct.h"
#include "region.h"
#include "objects/ship.h"
#include "objects/particle.h"
#include "objects/asteroid.h"
#include "objects/bullet.h"
#include "generic/collide.h"

struct GameManager gm_initialize(size_t region_size) {
    struct GameManager new_manager = {0};
    /* scratch_region can be used for stuff like returning a list of
       collisions between objects; resets each update loop */
    new_manager.scratch_region = new_region(region_size);
    new_manager.general_region = new_region(region_size);
    new_manager.particle_region = new_region(region_size);
    new_manager.asteroid_region = new_region(region_size);
    new_manager.bullet_region = new_region(region_size);

    new_manager.used_particles = NULL;
    new_manager.free_particles = NULL;
    new_manager.used_roids = NULL;
    new_manager.free_roids = NULL;
    new_manager.used_bullets = NULL;
    new_manager.free_bullets = NULL;

    return new_manager;
}

void gm_init_particles(struct GameManager *gm, int number_of_particles) {
    for (int i = 0; i < number_of_particles; i++) {
        Particle *new_part = create_particle(gm->particle_region);
        insert_particle_at_end(&gm->free_particles, new_part);
    }

    /* we probably shouldn't need more than 4096 asteroids, right? */
    for (int i = 0; i < 4096; i++) {
        Asteroid *new_roid = create_asteroid(gm->asteroid_region);
        insert_asteroid_at_end(&gm->free_roids, new_roid);
    }
}

void gm_update_all(struct GameManager *gm) {
    /* reset scratch region */
    region_reset(gm->scratch_region);
    
    /* update particles */
    update_particle_list(gm->used_particles, gm);
    clean_particle_list(&gm->used_particles, &gm->free_particles);

    /* update asteroids */
    update_asteroid_list(gm->used_roids);
}

void gm_draw_all(struct GameManager gm) {
    draw_particle_list(gm.used_particles);
    draw_asteroid_list(gm.used_roids);
}

void request_new_particle(struct GameManager *gm,
                          Vector2 pos, Vector2 velocity,
                          int lifetime, Colour col, float size) {
    if (gm->free_particles) {
        Particle *new_part = gm->free_particles;
        remove_particle_from_list(&gm->free_particles, new_part);

        set_particle(new_part,
                     pos, velocity, lifetime, col, size);
        insert_particle_at_end(&gm->used_particles, new_part);
    } else if (gm->used_particles) {
        Particle *new_part = gm->used_particles;
        remove_particle_from_list(&gm->used_particles, new_part);

        set_particle(new_part,
                     pos, velocity, lifetime, col, size);
        insert_particle_at_end(&gm->used_particles, new_part);
    }
}

void request_new_asteroid(struct GameManager *gm,
                          Vector2 pos, Vector2 velocity,
                          float size, float rot) {
    if (gm->free_roids) {
        Asteroid *new_roid = gm->free_roids;
        remove_asteroid_from_list(&gm->free_roids, new_roid);

        set_asteroid(new_roid,
                     pos, velocity, size, rot);
        insert_asteroid_at_end(&gm->used_roids, new_roid);
    } else if (gm->used_roids) {
        Asteroid *new_roid = gm->used_roids;
        remove_asteroid_from_list(&gm->used_roids, new_roid);

        set_asteroid(new_roid,
                     pos, velocity, size, rot);
        insert_asteroid_at_end(&gm->used_roids, new_roid);
    }
}

Asteroid *request_roid_collision_point(struct GameManager *gm, Vector2 point) {
    Asteroid *current = gm->used_roids;
    while (current) {
        if (collide_point(point,
                          current->offsets, current->offset_count,
                          current->pos)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
