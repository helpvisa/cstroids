#include "defs.h"
#include "structs.h"
#include "rng.h"
#include "objects/particle.h"
#include "objects/asteroid.h"
#include "objects/bullet.h"
#include "objects/ship.h"
#include "wrap_sdl/draw.h"
#include "wrap_sdl/init.h"
#include "wrap_sdl/input.h"
#include "generic/collide.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

extern App app;
extern struct ParticleNode *particles_head;
extern struct AsteroidNode *asteroids_head;
extern struct BulletNode *bullets_head;

extern Ship *player_ship;
extern int player_is_alive;

extern int screen_width;
extern int screen_height;

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
        {-6, -4},
        {-6, 4},
        {-10, 5},
        {10, 0}
    };
    player_ship = init_ship(init_pos, test_offsets, 5);

    // create an asteroid
    int secs_until_asteroid_spawn = 2;
    int ticks_since_last_spawn = 0;

    int last_ticks = SDL_GetTicks();
    while(1) {
        // wait for fixed timestep
        int ticks_since_last_frame = SDL_GetTicks() - last_ticks;
        if (ticks_since_last_frame < 1000 / DESIRED_FPS) {
            continue;
        }
        last_ticks = SDL_GetTicks();

        // spawn asteroids
        if (ticks_since_last_spawn > 1000 * secs_until_asteroid_spawn) {
            secs_until_asteroid_spawn = rng(18,6);
            ticks_since_last_spawn = 0;
            int top = rng(1, 0);
            int left = rng(1, 0);
            Vector2 roid_pos = {screen_width + 10, screen_height + 10};
            float x_vel_r = rng(2, 1);
            float y_vel_r = -rng(2, 1);
            if (left) {
                roid_pos.x = 0 - 10;
                x_vel_r = -rng(2, 1);
            }
            if (top) {
                roid_pos.y = 0 - 10;
                y_vel_r = rng(2, 1);
            }
            Vector2 vel_vec = {x_vel_r, y_vel_r};
            Asteroid *roid = create_asteroid(roid_pos, vel_vec, 1, x_vel_r);
            insert_asteroid_at_beginning(&asteroids_head, roid);
        } else {
            ticks_since_last_spawn += ticks_since_last_frame;
        }

        // setup the bg and parse inputs
        prepare_scene(0, 0, 0, 255);
        update_input();

        // update entities
        if (player_is_alive) {
            update_ship(player_ship);
        }
        update_particle_list(&particles_head);
        update_bullet_list(&bullets_head);
        update_asteroid_list(&asteroids_head);

        // draw objects
        update_window();
        draw_particle_list(particles_head);
        if (player_is_alive) {
            draw_ship(player_ship);
        }
        draw_bullet_list(bullets_head);
        draw_asteroid_list(asteroids_head);

        // present the final rendered scene
        // at a fixed rate of 60fps
        present_scene();
    }

    return 0;
}
