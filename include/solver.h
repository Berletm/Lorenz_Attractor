#ifndef SOLVER_H
#define SOLVER_H

#include "common.h"

void f_derrivative(vec3D_t* x, vec3D_t* fx, void* params);
void euler_step(vec3D_t* x0, vec3D_t* xh, double h, 
    void (*f)(vec3D_t*, vec3D_t*, void*), void* params);
void heun_step(vec3D_t* x0, vec3D_t* xh, double h, 
    void (*f)(vec3D_t*, vec3D_t*, void*), void* params);
void rk4_step(vec3D_t* x0, vec3D_t* xh, double h, 
    void (*f)(vec3D_t*, vec3D_t*, void*), void* params);
void integration_step(void (*method)(vec3D_t*, vec3D_t*, double, 
    void (*f)(vec3D_t*, vec3D_t*, void*), void*), double dt);

#endif