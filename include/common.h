#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

typedef struct vec3D {
    double x;
    double y;
    double z;
} vec3D_t;

extern vec3D_t camera_pos;
extern vec3D_t camera_target;
extern vec3D_t camera_up;
extern vec3D_t current_state;
extern vec3D_t points_buffer[];
extern int point_counter;
extern int buffer_index;
extern double params[];

#define CAMERA_SPEED 1.0f
#define BUFFER_SIZE 30000
#define WIDTH 1024
#define HEIGHT 768

#endif