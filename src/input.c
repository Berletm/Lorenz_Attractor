#include "input.h"
#include "common.h"
#include <math.h>

bool left_mouse_button_down = false;
int prev_mouse_x = 0;
int prev_mouse_y = 0;

void handle_input(SDL_Event* event) 
{
    vec3D_t camera_direction;
    camera_direction.x = camera_target.x - camera_pos.x;
    camera_direction.y = camera_target.y - camera_pos.y;
    camera_direction.z = camera_target.z - camera_pos.z;

    double length = sqrt(camera_direction.x * camera_direction.x +
                         camera_direction.y * camera_direction.y +
                         camera_direction.z * camera_direction.z);
    camera_direction.x /= length;
    camera_direction.y /= length;
    camera_direction.z /= length;

    vec3D_t camera_right;
    camera_right.x = camera_direction.y * camera_up.z - camera_direction.z * camera_up.y;
    camera_right.y = camera_direction.z * camera_up.x - camera_direction.x * camera_up.z;
    camera_right.z = camera_direction.x * camera_up.y - camera_direction.y * camera_up.x;

    length = sqrt(camera_right.x * camera_right.x +
                  camera_right.y * camera_right.y +
                  camera_right.z * camera_right.z);
    camera_right.x /= length;
    camera_right.y /= length;
    camera_right.z /= length;

    vec3D_t camera_up_vector;
    camera_up_vector.x = camera_right.y * camera_direction.z - camera_right.z * camera_direction.y;
    camera_up_vector.y = camera_right.z * camera_direction.x - camera_right.x * camera_direction.z;
    camera_up_vector.z = camera_right.x * camera_direction.y - camera_right.y * camera_direction.x;

    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_w:
                    camera_pos.x += camera_direction.x * CAMERA_SPEED;
                    camera_pos.y += camera_direction.y * CAMERA_SPEED;
                    camera_pos.z += camera_direction.z * CAMERA_SPEED;
                    camera_target.x += camera_direction.x * CAMERA_SPEED;
                    camera_target.y += camera_direction.y * CAMERA_SPEED;
                    camera_target.z += camera_direction.z * CAMERA_SPEED;
                    break;
                case SDLK_s:
                    camera_pos.x -= camera_direction.x * CAMERA_SPEED;
                    camera_pos.y -= camera_direction.y * CAMERA_SPEED;
                    camera_pos.z -= camera_direction.z * CAMERA_SPEED;
                    camera_target.x -= camera_direction.x * CAMERA_SPEED;
                    camera_target.y -= camera_direction.y * CAMERA_SPEED;
                    camera_target.z -= camera_direction.z * CAMERA_SPEED;
                    break;
                case SDLK_a:
                    camera_pos.x -= camera_right.x * CAMERA_SPEED;
                    camera_pos.y -= camera_right.y * CAMERA_SPEED;
                    camera_pos.z -= camera_right.z * CAMERA_SPEED;
                    camera_target.x -= camera_right.x * CAMERA_SPEED;
                    camera_target.y -= camera_right.y * CAMERA_SPEED;
                    camera_target.z -= camera_right.z * CAMERA_SPEED;
                    break;
                case SDLK_d:
                    camera_pos.x += camera_right.x * CAMERA_SPEED;
                    camera_pos.y += camera_right.y * CAMERA_SPEED;
                    camera_pos.z += camera_right.z * CAMERA_SPEED;
                    camera_target.x += camera_right.x * CAMERA_SPEED;
                    camera_target.y += camera_right.y * CAMERA_SPEED;
                    camera_target.z += camera_right.z * CAMERA_SPEED;
                    break;
                case SDLK_q:
                    camera_pos.x += camera_up_vector.x * CAMERA_SPEED;
                    camera_pos.y += camera_up_vector.y * CAMERA_SPEED;
                    camera_pos.z += camera_up_vector.z * CAMERA_SPEED;
                    camera_target.x += camera_up_vector.x * CAMERA_SPEED;
                    camera_target.y += camera_up_vector.y * CAMERA_SPEED;
                    camera_target.z += camera_up_vector.z * CAMERA_SPEED;
                    break;
                case SDLK_e:
                    camera_pos.x -= camera_up_vector.x * CAMERA_SPEED;
                    camera_pos.y -= camera_up_vector.y * CAMERA_SPEED;
                    camera_pos.z -= camera_up_vector.z * CAMERA_SPEED;
                    camera_target.x -= camera_up_vector.x * CAMERA_SPEED;
                    camera_target.y -= camera_up_vector.y * CAMERA_SPEED;
                    camera_target.z -= camera_up_vector.z * CAMERA_SPEED;
                    break;
            }
            break;
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
        if (left_mouse_button_down) {
            int deltaX = event->motion.x - prev_mouse_x;
            int deltaY = event->motion.y - prev_mouse_y;
            prev_mouse_x = event->motion.x;
            prev_mouse_y = event->motion.y;

            double angleY = deltaX * 0.0008f;
            double cosY = cos(angleY);
            double sinY = sin(angleY);

            vec3D_t dirY = {camera_target.x - camera_pos.x, camera_target.y - camera_pos.y, camera_target.z - camera_pos.z};
            double newX = dirY.x * cosY - dirY.z * sinY;
            double newZ = dirY.x * sinY + dirY.z * cosY;

            camera_target.x = camera_pos.x + newX;
            camera_target.z = camera_pos.z + newZ;

            double angleX = -1.0 * deltaY * 0.0008f;
            double cosX = cos(angleX);
            double sinX = sin(angleX);

            vec3D_t dirX = {camera_target.x - camera_pos.x, camera_target.y - camera_pos.y, camera_target.z - camera_pos.z};
            double newY = dirX.y * cosX - dirX.z * sinX;
            double newZ2 = dirX.y * sinX + dirX.z * cosX;

            camera_target.y = camera_pos.y + newY;
            camera_target.z = camera_pos.z + newZ2;
        }
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

