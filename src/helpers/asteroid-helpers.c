#include "../structs.h"
#include "../rng.h"
#include "../manager.h"
#include "../objects/asteroid.h"

void spawn_child_asteroids(struct GameManager *gm, Asteroid *parent,
                           float size_diff, int count) {
    for (int i = 0; i < count; i++) {
        float rand_x = ((float)rng(10, 0) - 5) / 10;
        float rand_y = ((float)rng(10, 0) - 5) / 10;
        Vector2 new_vel = {
            parent->velocity.x + parent->hit_influence.x + rand_x
                * ((2-parent->size) * 4),
            parent->velocity.y + parent->hit_influence.y + rand_y
                * ((2-parent->size) * 4)
        };
        Vector2 new_pos = {parent->pos.x, parent->pos.y};
        float new_size = parent->size - size_diff;
        request_new_asteroid(gm,
                             new_pos, new_vel, new_size, new_vel.x);
    }
}
