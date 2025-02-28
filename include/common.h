#ifndef COMMON_H
#define COMMON_H

#include <SDL2/SDL.h>

#define PI 3.14159265359
#define TO_RADIANS(deg) ((deg) * PI / 180.0)

#include <stdbool.h>

typedef struct vec3D {
    double x, y, z;
} vec3D_t;

vec3D_t vec3_add(vec3D_t a, vec3D_t b);

vec3D_t vec3_sub(vec3D_t a, vec3D_t b);

double vec3_dot(vec3D_t a, vec3D_t b);

vec3D_t vec3_cross(vec3D_t a, vec3D_t b);

vec3D_t vec3_scale(vec3D_t a, double scalar);

double vec3_mes(vec3D_t a);

vec3D_t vec3_normalize(vec3D_t a);

double vec3_angle(vec3D_t a, vec3D_t b);

static SDL_Window* window;
static SDL_GLContext context;

extern int width;
extern int height;
extern double fov;
extern double yaw;
extern double pitch;
extern vec3D_t camera_pos;
extern vec3D_t camera_direction;
extern vec3D_t camera_target;
extern vec3D_t camera_up;
extern vec3D_t current_state;
extern vec3D_t points_buffer[];
extern int point_counter;
extern int buffer_index;
extern double params[];

#define CAMERA_SPEED 1.0f
#define SENSITIVITY 0.1f
#define BUFFER_SIZE 30000

#endif