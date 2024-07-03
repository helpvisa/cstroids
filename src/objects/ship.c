#include "../defs.h"
#include "../structs.h"
#include "../rng.h"
#include "../wrap_sdl/draw.h"
#include "particle.h"
#include "bullet.h"
#include <math.h>

extern InputMap inputmap;
extern struct ParticleNode *particles_head;
extern struct BulletNode *bullets_head;

extern float ratio;
extern int bullet_count;

Ship *init_ship(Vector2 pos, Vector2 *offsets, int offset_count) {
    Vector2 zero = {0, 0};

    /* Ship ship = {pos, zero, 10, 0.03, 0, 3.5, offsets, offset_count}; */
    Ship *ship = malloc(sizeof(Ship));
    ship->pos = pos;
    ship->velocity = zero;
    ship->offsets = offsets;
    ship->offset_count = offset_count;
    ship->max_velocity = 10;
    ship->speed = 0.08;
    ship->angle = 0;
    ship->rot_speed = 3.5;
    ship->shot_cooldown = 0;

    return ship;
}

void update_ship(Ship *ship) {
    float amount_to_rotate = 0;
    float angle_rad = ship->angle * (PI / 180);
    float s = sin(angle_rad);
    float c = cos(angle_rad);
    ship->shot_cooldown -= 1;

    if (inputmap.shoot) {
        // spawn bullets
        if (bullet_count < 3 && ship->shot_cooldown < 1) {
            ship->shot_cooldown = 5;
            bullet_count += 1;
            Vector2 bullet_origin = {ship->pos.x + c * 10, ship->pos.y + s * 10};
            Vector2 bullet_vel = {10 * c, 10 * s};
            Colour bullet_col = {0, 255, 0, 255};
            Bullet *bullet = create_bullet(bullet_origin, bullet_vel, bullet_col, 40);
            insert_bullet_at_end(&bullets_head, bullet);
        }
    }
    if (inputmap.up) {
        // activate thrusters
        ship->velocity.x += c * ship->speed;
        ship->velocity.y += s * ship->speed;
        // clamp speed
        if (ship->velocity.x > ship->max_velocity) {
            ship->velocity.x = ship->max_velocity;
        } else if (ship->velocity.x < -ship->max_velocity) {
            ship->velocity.x = -ship->max_velocity;
        }
        if (ship->velocity.y > ship->max_velocity) {
            ship->velocity.y = ship->max_velocity;
        } else if (ship->velocity.y < -ship->max_velocity) {
            ship->velocity.y = -ship->max_velocity;
        }
        // create engine particles
        float x_rand = (float)rng(10, 0) / 10;
        float y_rand = (float)rng(10, 0) / 10;
        float col_rand = (float)rng(60, 0);
        Colour col = {255 - col_rand, 150 + col_rand, 0, 255};
        Vector2 part_origin = {ship->pos.x + c * -10 + x_rand - 0.5,
                                ship->pos.y + s * -10 + y_rand - 0.5};
        Vector2 part_vel = {ship->velocity.x + c * -4 + (x_rand - 0.5) * 2,
                            ship->velocity.y + s * -4 + (y_rand - 0.5) * 2};
        Particle *new_part = create_particle(part_origin,
                                                part_vel,
                                                60 * 30,
                                                col,
                                                col_rand / 10);
        insert_particle_at_end(&particles_head, new_part);
    }
    if (inputmap.left) {
        ship->angle -= ship->rot_speed;
        amount_to_rotate -= ship->rot_speed;
    }
    if (inputmap.right) {
        ship->angle += ship->rot_speed;
        amount_to_rotate += ship->rot_speed;
    }

    float rotation_angle = amount_to_rotate * (PI / 180);
    float rs = sin(rotation_angle);
    float rc = cos(rotation_angle);

    for (int i = 0; i < ship->offset_count; i++) {
        // rotate
        float new_x = rc * ship->offsets[i].x - rs * ship->offsets[i].y;
        float new_y = rs * ship->offsets[i].x + rc * ship->offsets[i].y;
        ship->offsets[i].x = new_x;
        ship->offsets[i].y = new_y;
    }

    // move ship based on velocity
    ship->pos.x += ship->velocity.x;
    ship->pos.y += ship->velocity.y;
    // wrap ship back across borders
    if (ship->pos.x > DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 10) {
        ship->pos.x = -10;
    } else if (ship->pos.x < -10) {
        ship->pos.x = DEFAULT_SCREEN_WIDTH * (ratio / DEFAULT_RATIO) + 10;
    }
    if (ship->pos.y > DEFAULT_SCREEN_HEIGHT + 10) {
        ship->pos.y = -10;
    } else if (ship->pos.y < -10) {
        ship->pos.y = DEFAULT_SCREEN_HEIGHT + 10;
    }
}

void draw_ship(Ship *ship) {
    Vector2 points[ship->offset_count + 1];
    for (int i = 0; i < ship->offset_count; i++) {
        Vector2 global_point_position = {ship->pos.x + ship->offsets[i].x,
                                         ship->pos.y + ship->offsets[i].y};
        points[i] = global_point_position;
    }
    // duplicate first point to close the poly
    points[ship->offset_count] = points[0];

    Colour col = {255, 255, 255, 255};
    render_polygon(points, ship->offset_count + 1, col);
}
