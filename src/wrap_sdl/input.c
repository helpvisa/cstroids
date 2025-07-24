/*
   Copyright 2025 Daniel Brackenbury

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "../structs.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>

InputMap inputmap = {0, 0, 0, 0, 0};

void key_down(SDL_KeyboardEvent *event) {
    if (event->repeat == 0) {
        switch (event->keysym.scancode) {
        case SDL_SCANCODE_UP:
            inputmap.up = 1;
            break;
        case SDL_SCANCODE_LEFT:
            inputmap.left = 1;
            break;
        case SDL_SCANCODE_RIGHT:
            inputmap.right = 1;
            break;
        case SDL_SCANCODE_SPACE:
            inputmap.shoot = 1;
            break;
        case SDL_SCANCODE_Z:
        case SDL_SCANCODE_X:
            inputmap.shoot = 1;
            break;
        case SDL_SCANCODE_R:
            inputmap.reset = 1;
        default:
            break;
        }
    }
}

void key_up(SDL_KeyboardEvent *event) {
    if (event->repeat == 0) {
        switch (event->keysym.scancode) {
        case SDL_SCANCODE_UP:
            inputmap.up = 0;
            break;
        case SDL_SCANCODE_LEFT:
            inputmap.left = 0;
            break;
        case SDL_SCANCODE_RIGHT:
            inputmap.right = 0;
            break;
        case SDL_SCANCODE_SPACE:
            inputmap.shoot = 0;
            break;
        case SDL_SCANCODE_Z:
        case SDL_SCANCODE_X:
            inputmap.shoot = 0;
            break;
        case SDL_SCANCODE_R:
            inputmap.reset = 0;
            break;
        default:
            break;
        }
    }
}

void update_input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
            key_down(&event.key);
            break;
        case SDL_KEYUP:
            key_up(&event.key);
            break;
        default:
            break;
        }
    }
}
