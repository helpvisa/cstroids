#include "../structs.h"
#include "../wrap_sdl/input.h"
#include "../wrap_sdl/draw.h"

extern InputMap inputmap;

// create and return a player ship
Ship init_ship(Vector2 pos, Vector2 *offsets, int offset_count) {
    Vector2 zero = {0, 0};
    Ship ship = {pos, zero, 0, offsets, offset_count};
    return ship;
}

void update_ship(Ship *ship) {
    // debug keys
    if (inputmap.up) {
        ship->speed.y -= 0.1;
    }
    if (inputmap.left) {
        ship->speed.x -= 0.1;
    }
    if (inputmap.right) {
        ship->speed.x += 0.1;
    }
    if (inputmap.shoot) {
        ship->speed.y += 0.1;
    }

    for (int i = 0; i < ship->offset_count; i++) {
        ship->offsets[i].x += ship->speed.x;
        ship->offsets[i].y += ship->speed.y;
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
