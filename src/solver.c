#include "solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPSILON 1e-8

void f_derrivative(vec3D_t* x, vec3D_t* fx, void* params) 
{
    double sigma = *(((double*)params) + 0);
    double rho = *(((double*)params) + 1);
    double betta = *(((double*)params) + 2);

    fx->x = sigma * (x->y - x->x);
    fx->y = x->x * (rho - x->z) - x->y;
    fx->z = x->x * x->y - betta * x->z;
}

void euler_step(vec3D_t* x0, vec3D_t* xh, double h, 
    void (*f)(vec3D_t*, vec3D_t*, void*), void* params) 
{
    vec3D_t* fx = (vec3D_t*)malloc(sizeof(vec3D_t));
    f(x0, fx, params);

    xh->x = x0->x + h * fx->x;
    xh->y = x0->y + h * fx->y;
    xh->z = x0->z + h * fx->z;

    free(fx);
}

void heun_step(vec3D_t* x0, vec3D_t* xh, double h, 
    void (*f)(vec3D_t*, vec3D_t*, void*), void* params) 
{
    vec3D_t* fx = (vec3D_t*)malloc(sizeof(vec3D_t));
    vec3D_t* k1 = (vec3D_t*)malloc(sizeof(vec3D_t));

    f(x0, fx, params);
    
    memcpy(k1, fx, sizeof(vec3D_t));
    
    xh->x = x0->x + k1->x * h;
    xh->y = x0->y + k1->y * h;
    xh->z = x0->z + k1->z * h;

    f(xh, fx, params);

    xh->x = x0->x + 0.5 * h * (k1->x + fx->x);
    xh->y = x0->y + 0.5 * h * (k1->y + fx->y);
    xh->z = x0->z + 0.5 * h * (k1->z + fx->z);

    free(fx);
    free(k1);
}

void rk4_step(vec3D_t* x0, vec3D_t* xh, double h, 
    void (*f)(vec3D_t*, vec3D_t*, void*), void* params) 
{
    vec3D_t* fx = (vec3D_t*)malloc(sizeof(vec3D_t));
    vec3D_t* k = (vec3D_t*)malloc(sizeof(vec3D_t) * 4);

    double weights[] = {0.5, 0.5, 1.0};
    double final_weights[] = {1.0 / 6.0, 1.0 / 3.0, 1.0 / 3.0, 1.0 / 6.0};

    for (int i = 0; i < 3; i++) {
        f(i == 0 ? x0 : xh, fx, params);
        memcpy(&k[i], fx, sizeof(vec3D_t));

        xh->x = x0->x + h * weights[i] * k[i].x;
        xh->y = x0->y + h * weights[i] * k[i].y;
        xh->z = x0->z + h * weights[i] * k[i].z;
    }

    f(xh, fx, params);
    memcpy(&k[3], fx, sizeof(vec3D_t));

    xh->x = x0->x + h * (final_weights[0] * k[0].x + final_weights[1] * k[1].x + final_weights[2] * k[2].x + final_weights[3] * k[3].x);
    xh->y = x0->y + h * (final_weights[0] * k[0].y + final_weights[1] * k[1].y + final_weights[2] * k[2].y + final_weights[3] * k[3].y);
    xh->z = x0->z + h * (final_weights[0] * k[0].z + final_weights[1] * k[1].z + final_weights[2] * k[2].z + final_weights[3] * k[3].z);

    free(fx);
    free(k);
}

void integrate(vec3D_t* x0, double T, double h, void (*f)(vec3D_t*, vec3D_t*, void*),
    void (*step) (vec3D_t*, vec3D_t*, double, void (*f)(vec3D_t*, vec3D_t*, void*), void*), 
    void* params)
{
    double t;

    vec3D_t* x = (vec3D_t*)malloc(sizeof(vec3D_t));
    vec3D_t* xh = (vec3D_t*)malloc(sizeof(vec3D_t));

    memcpy(x, x0, sizeof(vec3D_t));

    for (t = 0; t < T; ++t) {
        printf("%lf %lf %lf\n", x->x, x->y, x->z);

        step(x, xh, h, f, params);
        memcpy(x, xh, sizeof(vec3D_t));
    }

    free(x);
    free(xh);
}

void integration_step(void (*method)(vec3D_t*, vec3D_t*, double, 
    void (*f)(vec3D_t*, vec3D_t*, void*), void*), double dt)
{
    points_buffer[buffer_index] = current_state;
    buffer_index = (buffer_index + 1) % BUFFER_SIZE;
    if (point_counter < BUFFER_SIZE) {
        point_counter++;
    }

    method(&current_state, &current_state, dt, f_derrivative, params);
}

void implicit_trapezoidal_step(vec3D_t* x0, vec3D_t* xh, double h, void (*f)(vec3D_t*, vec3D_t*, void*), void* params) {
    vec3D_t fx, k1;

    f(x0, &fx, params);
    k1 = fx;

    newton_approximation(x0, xh, h, f, params);

    f(xh, &fx, params);

    xh->x = x0->x + 0.5 * h * (k1.x + fx.x);
    xh->y = x0->y + 0.5 * h * (k1.y + fx.y);
    xh->z = x0->z + 0.5 * h * (k1.z + fx.z);
}

void newton_approximation(vec3D_t* x0, vec3D_t* xh_approximation, double h, void (*f)(vec3D_t*, vec3D_t*, void*), void* params) {
    vec3D_t current_approximation = *x0;
    vec3D_t next_approximation;
    vec3D_t Fx, F_dotx;
    vec3D_t delta;

    do {
        F(x0, &current_approximation, &Fx, h, f, params);
        F_dot(&current_approximation, &F_dotx, h, params);

        next_approximation.x = current_approximation.x - (Fx.x / F_dotx.x);
        next_approximation.y = current_approximation.y - (Fx.y / F_dotx.y);
        next_approximation.z = current_approximation.z - (Fx.z / F_dotx.z);

        delta.x = next_approximation.x - current_approximation.x;
        delta.y = next_approximation.y - current_approximation.y;
        delta.z = next_approximation.z - current_approximation.z;

        current_approximation = next_approximation;
    } while (l2_mes(&delta) >= EPSILON);

    *xh_approximation = current_approximation;
}

double l2_mes(vec3D_t* x) {
    return sqrt(pow(x->x, 2) + pow(x->y, 2) + pow(x->z, 2));
}

void F(vec3D_t* x0, vec3D_t* xh, vec3D_t* Fx, double h, void (*f)(vec3D_t*, vec3D_t*, void*), void* params) {
    vec3D_t fx, fxh;
    f(x0, &fx, params);
    f(xh, &fxh, params);

    Fx->x = xh->x - x0->x - 0.5 * h * (fx.x + fxh.x);
    Fx->y = xh->y - x0->y - 0.5 * h * (fx.y + fxh.y);
    Fx->z = xh->z - x0->z - 0.5 * h * (fx.z + fxh.z);
}

void F_dot(vec3D_t* xh, vec3D_t* F_dotx, double h, void* params)
{
    F_dotx->x = 1 - 0.5f * h * (-((double*)params)[0]);
    F_dotx->y = 1 - 0.5f * h * (-1);
    F_dotx->z = 1 - 0.5f * h * (-((double*)params)[2]);
}