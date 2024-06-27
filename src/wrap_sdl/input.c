#include <SDL2/SDL_events.h>

void catch_input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;

            default:
                break;
        }
    }
}
