#include "../defs.h"
#include "../structs.h"
#include "../wrap_sdl/draw.h"
#include <math.h>

#define PI 3.1415926535

extern InputMap inputmap;

extern float zoom_x;
extern float zoom_y;
extern float ratio;
extern int screen_width;
extern int screen_height;

Ship init_ship(Vector2 pos, Vector2 *offsets, int offset_count) {
    Vector2 zero = {0, 0};

    Ship ship = {pos, zero, 10, 0.03, 0, 3.5, offsets, offset_count};
    return ship;
}

void update_ship(Ship *ship) {
    float amount_to_rotate = 0;
    float angle_rad = ship->angle * (PI / 180);
    float s = sin(angle_rad);
    float c = cos(angle_rad);

    if (inputmap.up) {
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
        Vector2 global_point_position = {(ship->pos.x + ship->offsets[i].x) * zoom_x,
                                         (ship->pos.y + ship->offsets[i].y) * zoom_y};
        points[i] = global_point_position;
    }
    // duplicate first point to close the poly
    points[ship->offset_count] = points[0];

    Colour col = {255, 255, 255, 255};
    render_polygon(points, ship->offset_count + 1, col);
}
