#include "input.h"
#include "common.h"
#include <math.h>

bool left_mouse_button_down = false;
int prev_mouse_x = 0;
int prev_mouse_y = 0;

void handle_input(SDL_Event* event)
{
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) 
            {
                case SDLK_w: camera_pos = vec3_add(camera_pos, vec3_scale(camera_direction, CAMERA_SPEED)); break;
                case SDLK_a: camera_pos = vec3_sub(camera_pos, vec3_scale(vec3_normalize(vec3_cross(camera_direction, camera_up)), CAMERA_SPEED)); break;
                case SDLK_s: camera_pos = vec3_sub(camera_pos, vec3_scale(camera_direction, CAMERA_SPEED)); break;
                case SDLK_d: camera_pos = vec3_add(camera_pos, vec3_scale(vec3_normalize(vec3_cross(camera_direction, camera_up)), CAMERA_SPEED)); break;
                case SDLK_q: camera_pos = vec3_add(camera_pos, vec3_scale(camera_up, CAMERA_SPEED)); break;
                case SDLK_e: camera_pos = vec3_sub(camera_pos, vec3_scale(camera_up, CAMERA_SPEED)); break;
            }
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                left_mouse_button_down = true;
                prev_mouse_x = event->button.x;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event->button.button == SDL_BUTTON_LEFT) {
                left_mouse_button_down = false;
            }
            break;
        case SDL_MOUSEMOTION:
            if (left_mouse_button_down) 
            {
                double delta_x = event->motion.xrel;
                double delta_y = event->motion.yrel;

                yaw += delta_x * SENSITIVITY;
                pitch -= delta_y * SENSITIVITY;
                
                if (pitch > 89.0)
                {
                    pitch = 89.0;
                }
                if (pitch < -89.0)
                {
                    pitch = -89.0;
                }
            }
            break;
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_RESIZED) {
                int new_width = event->window.data1;
                int new_height = event->window.data2;

                glViewport(0, 0, new_width, new_height);
            }
            break;
        case SDL_MOUSEWHEEL:
            fov -= 5 * event->wheel.y;

            if (fov < 5) fov = 5;
            if (fov > 120) fov = 120;
            
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(fov, (double)width / height, 0.1, 300.0);
            glMatrixMode(GL_MODELVIEW);
            SDL_GL_SwapWindow(window);
            break;
    }
}

bool process_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: return false;
            default:
                handle_input(&event);
                break;
        }
    }
    return true;
}
