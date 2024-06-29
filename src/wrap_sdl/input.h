#include "../structs.h"
#include <SDL2/SDL_events.h>

#ifndef INPUT_H_
#define INPUT_H_

InputMap init_inputmap();
void key_down(SDL_KeyboardEvent *event);
void key_up(SDL_KeyboardEvent *event);
void update_input();

#endif
