#include <SDL2/SDL.h>
#include <stdlib.h>

#define IMPLEMENT_REGIONS
#define DEBUG_REGIONS
#include "region.h"

#include "defs.h"
#include "structs.h"
#include "rng.h"
#include "manager.h"
#include "objects/particle.h"
#include "objects/asteroid.h"
#include "objects/bullet.h"
#include "objects/ship.h"
#include "wrap_sdl/draw.h"
#include "wrap_sdl/init.h"
#include "wrap_sdl/input.h"
#include "generic/collide.h"
#include "game.h"

extern App app;
extern InputMap inputmap;

extern Ship *player_ship;
extern int player_is_alive;

extern int screen_width;
extern int screen_height;

const unsigned int DELAY_TIME = 1000.0 / DESIRED_FPS;

int main(int argc, char *argv[]) {
    // move cursor down two blocks for debug info
    printf("\n\n");

    init_SDL("CStroids");
    atexit(cleanup_SDL);

    // parse argc and argv
    int max_particle_count = 10000;
    if (argc > 1) {
        printf("value of argv[1] is %s\n", argv[1]);
        max_particle_count = strtof(argv[1], NULL);
    }

    // create the "game manager"
    struct GameManager game_manager = gm_initialize(REGION_SIZE);
    gm_init_all(&game_manager, max_particle_count, MAX_BULLETS);

    // initialize random number generator
    init_rng();

    // used for tracking game state
    int prev_player_state = 1;

    // create a ship
    Vector2 init_pos = {DEFAULT_SCREEN_WIDTH/2.0, DEFAULT_SCREEN_HEIGHT/2.0};
    Vector2 test_offsets[] = {
        {-10, -5},
        {-6, -4},
        {-6, 4},
        {-10, 5},
        {10, 0}
    };
    player_ship = create_ship(game_manager.general_region);
    set_ship(player_ship, init_pos, test_offsets, 5);

    // create an asteroid
    unsigned int secs_until_asteroid_spawn = 2;
    unsigned int ticks_since_last_spawn = 0;

    unsigned int frame_start, frame_time = 0;
    while(1) {
        frame_start = SDL_GetTicks();

        // reset the game
        if (inputmap.reset) {
            inputmap.reset = 0;
            Vector2 test_offsets[] = {
                {-10, -5},
                {-6, -4},
                {-6, 4},
                {-10, 5},
                {10, 0}
            };
            reset_game(&game_manager, player_ship, test_offsets,
                       &player_is_alive, init_pos);
        }

        // spawn asteroids
        if (player_is_alive &&
            ticks_since_last_spawn > DESIRED_FPS * secs_until_asteroid_spawn) {
            secs_until_asteroid_spawn = rng(12,1);
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
            request_new_asteroid(&game_manager,
                                 roid_pos, vel_vec, 1.6, vel_vec.x);
        } else {
            ticks_since_last_spawn += 1;
        }

        // setup the bg and parse inputs
        prepare_scene(0, 0, 0, 255);
        update_input();

        // update entities
        if (player_is_alive) {
            update_ship(player_ship, &game_manager);
        }
        gm_update_all(&game_manager);

        // draw objects
        update_window();
        if (player_is_alive) {
            draw_ship(player_ship);
        }
        gm_draw_all(game_manager);

        // present the final rendered scene
        // at a fixed rate of 60fps
        present_scene();

        // perform some game state checks
        // did the player just die?
        if (!player_is_alive && prev_player_state) {
            // do nothing for now
            ;
        }
        // update vars used to track state in previous frame
        prev_player_state = player_is_alive;

        // fixed time-step
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < DELAY_TIME) {
            SDL_Delay((unsigned int)(DELAY_TIME - frame_time));
        }

        // debug information
        printf("\e[A\e[A");
        printf("                           \n");
        /* printf("                           \n"); */
        /* printf("\e[A\e[A"); */
        /* print_region(game_manager.asteroid_region, 'k'); */
        /* visualize_region(game_manager.asteroid_region, 1024 * 32); */
        printf("Score: %20d\n", game_manager.score);
    }

    return 0;
}
