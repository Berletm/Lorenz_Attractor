#include "window.h"
#include "common.h"

void init_window() 
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Lorenz Attractor", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    context = SDL_GL_CreateContext(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, (double)width / height, 0.1, 300.0);
}

void deinit_window() 
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void update_camera() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    camera_direction.x = cos(TO_RADIANS(yaw)) * cos(TO_RADIANS(pitch));
    camera_direction.y = sin(TO_RADIANS(pitch));
    camera_direction.z = sin(TO_RADIANS(yaw)) * cos(TO_RADIANS(pitch));

    camera_target = vec3_add(camera_pos, camera_direction);

    gluLookAt(camera_pos.x, camera_pos.y, camera_pos.z,
              camera_target.x, camera_target.y, camera_target.z,
              camera_up.x, camera_up.y, camera_up.z);
}

void draw_axes() 
{
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 50.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 50.0);
    glEnd();
}

void draw() 
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    draw_axes();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 0.5f, 1.0f);

    for (int i = buffer_index; i < point_counter; ++i) {
        vec3D_t point = points_buffer[i];
        glVertex3f(point.x, point.y, point.z);
    }

    for (int i = 0; i < buffer_index; ++i) {
        vec3D_t point = points_buffer[i];
        glVertex3f(point.x, point.y, point.z);
    }

    glEnd();

    glPointSize(3.0);
    glBegin(GL_POINTS);
    glColor3f(0.5f, 0.5f, 0.0f);
    glVertex3f(current_state.x, current_state.y, current_state.z);
    glEnd();

    SDL_GL_SwapWindow(window);
}
