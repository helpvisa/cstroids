#include <math.h>
#include "../defs.h"
#include "../structs.h"
#include "../rng.h"
#include "../objects/particle.h"
#include "../globals.h"
#include "../region.h"
#include "../manager.h"

void create_particle_fan(float shift, Vector2 pos,
                         Colour col, int lifetime, float size,
                         float vel_mult, float rand_mult,
                         struct GameManager *gm) {
    for (float angle = 0; angle < 2 * PI; angle += shift) {
        float s = sin(angle);
        float c = cos(angle);

        float x_rand = (float)rng(10, 0) / 10;
        float y_rand = (float)rng(10, 0) / 10;
        float x_rand_m = x_rand * rand_mult;
        float y_rand_m = y_rand * rand_mult;

        Vector2 part_vel = {c + (x_rand - 0.5) / 2 * vel_mult,
                            s + (y_rand - 0.5) / 2 * vel_mult};
        Colour part_col = {col.r + y_rand_m,
                           col.g + x_rand_m / 2 + y_rand_m / 2,
                           col.b + x_rand_m,
                           col.a};

        int particle_lifetime = lifetime * (10 + x_rand + y_rand);

        request_new_particle(gm, pos, part_vel, particle_lifetime, part_col,
                             size + x_rand + y_rand);
    }
}
