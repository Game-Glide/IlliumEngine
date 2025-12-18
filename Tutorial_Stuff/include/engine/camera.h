#ifndef CAMERA_H
#define CAMERA_H
#include <cglm/cglm.h>
void update_camera(mat4 view_mat);
void init_camera(vec3 camera_pos, vec3 camera_front, vec3 camera_up);
#endif

#ifdef CAMERA_CONST_H
mat4 view_mat = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f}
};
#endif

#ifdef CAMERA_VARS_H
extern vec3* CAMERA_POS;
extern vec3* CAMERA_FRONT;
extern vec3* CAMERA_UP;

extern float* yaw;
extern float* pitch;
#endif