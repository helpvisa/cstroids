#include "manager_struct.h"
#include "region.h"

struct GameManager gm_initialize(size_t region_size);
void gm_init_particles(struct GameManager *gm, int number_of_particles);
void gm_update_all(struct GameManager *gm);
void gm_draw_all(struct GameManager gm);

void request_new_particle(struct GameManager *gm,
                          Vector2 pos, Vector2 velocity,
                          int lifetime, Colour col, float size);
