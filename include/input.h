#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

bool process_input();
void handle_input(SDL_Event* event);

#endif