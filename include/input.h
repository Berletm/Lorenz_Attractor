#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdbool.h>

bool process_input();
void handle_input(SDL_Event* event);

#endif