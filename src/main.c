#include "defs.h"
#include "structs.h"
#include "rng.h"
#include "objects/particle.h"
#include "objects/asteroid.h"
#include "objects/ship.h"
#include "wrap_sdl/draw.h"
#include "wrap_sdl/init.h"
#include "wrap_sdl/input.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

extern App app;
extern struct ParticleNode *particles_head;
extern struct AsteroidNode *asteroids_head;

int main(int argc, char *argv[]) {
    memset(&app, 0, sizeof(App));

    init_SDL("CStroids");
    atexit(cleanup_SDL);

    // initialize random number generator
    init_rng();

    // create a ship
    Vector2 init_pos = {DEFAULT_SCREEN_WIDTH/2.0, DEFAULT_SCREEN_HEIGHT/2.0};
    Vector2 test_offsets[] = {
        {-10, -5},
        {-10, 5},
        {10, 0}
    };
    Ship testship = init_ship(init_pos, test_offsets, 3);

    // create an asteroid
    Vector2 roid_pos = {60, 60};
    Vector2 vel_vec = {1, 1};
    Asteroid *testroid = create_asteroid(roid_pos, vel_vec, 1, 1);
    insert_asteroid_at_beginning(&asteroids_head, testroid);

    int last_ticks = SDL_GetTicks();
    while(1) {
        // wait for fixed timestep
        if (SDL_GetTicks() - last_ticks < 1000 / DESIRED_FPS) {
            continue;
        }
        last_ticks = SDL_GetTicks();

        // setup the bg and parse inputs
        prepare_scene(0, 0, 0, 255);
        update_input();

        // update entities
        update_ship(&testship);
        update_particle_list(&particles_head);
        update_asteroid_list(&asteroids_head);

        // draw objects
        update_window();
        draw_ship(&testship);
        draw_particle_list(particles_head);
        draw_asteroid_list(asteroids_head);

        // present the final rendered scene
        // at a fixed rate of 60fps
        present_scene();
    }

    return 0;
}
