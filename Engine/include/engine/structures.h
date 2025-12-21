#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "GLFW/glfw3.h"
#include "cglm/mat4.h"

struct Engine {
    float delta_time, last_time;
    int height, width;
    const char* title;
    GLFWwindow* window;
} typedef Engine;

struct Renderer {
    mat4 view_mat, projection_mat;
} typedef Renderer;

#endif