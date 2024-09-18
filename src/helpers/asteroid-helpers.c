#include "../structs.h"
#include "../rng.h"
#include "../objects/asteroid.h"

void spawn_child_asteroids(struct AsteroidNode **head, Asteroid *roid, Vector2 influence, float size_diff, int count) {
    for (int i = 0; i < count; i++) {
        float rand_x = ((float)rng(10, 0) - 5) / 10;
        float rand_y = ((float)rng(10, 0) - 5) / 10;
        Vector2 new_vel = {roid->velocity.x + influence.x + rand_x * ((2 - roid->size) * 4),
                           roid->velocity.y + influence.y + rand_y * ((2 - roid->size) * 4)};
        Vector2 new_pos = {roid->pos.x, roid->pos.y};
        float new_size = roid->size - size_diff;
        Asteroid *new_roid = create_asteroid(new_pos, new_vel, new_size, new_vel.x);
        insert_asteroid_at_end(head, new_roid);
    }
}
