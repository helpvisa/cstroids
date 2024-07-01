#include "../structs.h"

// check a collision between a point and a set of vector offsets
int collide_point(Vector2 p, Vector2 *o, int o_count, Vector2 o_offset) {
    int collision = 0;

    int next = 0;
    for (int current = 0; current < o_count; current++) {
        // we need both current and next point in polygon; we wrap
        next = current + 1;
        if (next == o_count) {
            next = 0;
        }
        Vector2 vc = o[current];
        vc.x += o_offset.x;
        vc.y += o_offset.y;
        Vector2 vn = o[next];
        vn.x += o_offset.x;
        vn.y += o_offset.y;

        // compare and flip collision bit
        if (((vc.y >= p.y && vn.y < p.y) || (vc.y < p.y && vn.y >= p.y)) &&
            (p.x < (vn.x - vc.x) * (p.y - vc.y) / (vn.y - vc.y) + vc.x)) {
                collision = !collision;
        }
    }

    return collision;
}

// check a collision between two sets of vector offsets
int collide_polygons(Vector2 *o1, int o1_count, Vector2 o1_offset, Vector2 *o2, int o2_count, Vector2 o2_offset) {
    // we check each point of o1 against each point of o2
    for (int i = 0; i < o1_count; i++) {
        int collision = 0;
        Vector2 p = o1[i];
        p.x += o1_offset.x;
        p.y += o1_offset.y;
        int next = 0;
        for (int current = 0; current < o2_count; current++) {
            // we need both current and next point in polygon; we wrap
            next = current + 1;
            if (next == o2_count) {
                next = 0;
            }
            Vector2 vc = o2[current];
            vc.x += o2_offset.x;
            vc.y += o2_offset.y;
            Vector2 vn = o2[next];
            vn.x += o2_offset.x;
            vn.y += o2_offset.y;

            // compare and flip collision bit
            if (((vc.y >= p.y && vn.y < p.y) || (vc.y < p.y && vn.y >= p.y)) &&
                (p.x < (vn.x - vc.x) * (p.y - vc.y) / (vn.y - vc.y) + vc.x)) {
                    collision = !collision;
            }
        }
        if (collision) {
            return 1;
        }
    }

    // if we got this far, there's been no collision
    return 0;
}
