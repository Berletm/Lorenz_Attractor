#include "common.h"
#include <math.h>

double pitch = 0.0;
double yaw = -90.0;

double fov = 45.0;

int width = 1024;
int height = 768;

vec3D_t camera_pos = {20.0, 20.0, 150.0};
vec3D_t camera_target = {0.0, 0.0, 0.0};
vec3D_t camera_direction = {0.0, 0.0, -1.0};
vec3D_t camera_up = {0.0, 1.0, 0.0};
vec3D_t current_state = {0.001, 0.0, 0.0};
vec3D_t points_buffer[BUFFER_SIZE];
int point_counter = 0;
int buffer_index = 0;

// params[0] = sigma, params[1] = rho, params[2] = betta
double params[3] = {10.0, 28.0, 8.0 / 3.0};

vec3D_t vec3_add(vec3D_t a, vec3D_t b) 
{
    vec3D_t res = {a.x + b.x, a.y + b.y, a.z + b.z};
    return res;
}

vec3D_t vec3_sub(vec3D_t a, vec3D_t b) 
{
    vec3D_t res = {a.x - b.x, a.y - b.y, a.z - b.z};
    return res;
}

double vec3_dot(vec3D_t a, vec3D_t b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3D_t vec3_cross(vec3D_t a, vec3D_t b) 
{
    vec3D_t result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

vec3D_t vec3_scale(vec3D_t a, double scalar)
{
    vec3D_t res = {a.x * scalar, a.y * scalar, a.z * scalar};
    return res;
}

double vec3_mes(vec3D_t a)
{
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

vec3D_t vec3_normalize(vec3D_t a)
{
    double len = vec3_mes(a);
    vec3D_t res = {a.x / len, a.y / len, a.z / len};
    return res;
}

double vec3_angle(vec3D_t a, vec3D_t b)
{
    double dot = vec3_dot(a, b);
    double len_a = vec3_mes(a);
    double len_b = vec3_mes(b);
    return acos(dot / (len_a * len_b));
}