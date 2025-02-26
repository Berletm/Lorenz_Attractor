#include "common.h"

vec3D_t camera_pos = {100.0, 60.0, 0.0};
vec3D_t camera_target = {0.0, 0.0, 0.0};
vec3D_t camera_up = {0.0, 1.0, 0.0};
vec3D_t current_state = {0.001, 0.0, 0.0};
vec3D_t points_buffer[BUFFER_SIZE];
int point_counter = 0;
int buffer_index = 0;
double params[3] = {10.0, 28.0, 8.0 / 3.0};