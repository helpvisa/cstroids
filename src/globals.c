#include "defs.h"
#include "structs.h"

// rendering
App app = {NULL, NULL};
float zoom_x = 1;
float zoom_y = 1;
float ratio = DEFAULT_RATIO;
int screen_width = DEFAULT_SCREEN_WIDTH;
int screen_height = DEFAULT_SCREEN_HEIGHT;

// linked lists
struct ParticleNode *particles_head = NULL;
struct AsteroidNode *asteroids_head = NULL;
