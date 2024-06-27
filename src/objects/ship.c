#include "../structs.h"
#include "../wrap_sdl/draw.h"

// create and return a player ship
Ship init_ship(Vector2 pos, Vector2 *offsets, int offset_count) {
    Vector2 zero = {0, 0};
    Ship ship = {pos, zero, 0, offsets, offset_count};
    return ship;
}

void draw_ship(Ship ship) {
    Vector2 points[ship.offset_count];
    for (int i = 0; i < ship.offset_count; i++) {
        Vector2 global_point_position = {ship.pos.x + ship.offsets[i].x,
                                         ship.pos.y + ship.offsets[i].y};
        points[i] = global_point_position;
    }

    Colour col = {255, 255, 255, 255};
    render_polygon(points, ship.offset_count, col);
}
