#include <stdlib.h>
#include <time.h>

void init_rng() {
    srand(time(NULL));
}

int rng(int max, int min) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}
