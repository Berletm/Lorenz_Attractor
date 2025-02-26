#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

void init_window();
void deinit_window();
void update_camera();
void draw();

#endif