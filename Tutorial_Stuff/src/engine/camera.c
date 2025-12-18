#define CAMERA_VARS_H
#include <engine/camera.h>

vec3* CAMERA_POS = NULL;
vec3* CAMERA_FRONT = NULL;
vec3* CAMERA_UP = NULL;
float* yaw = NULL;
float* pitch = NULL;

void init_camera(vec3 camera_pos, vec3 camera_front, vec3 camera_up) {
    CAMERA_POS = (vec3*)malloc(sizeof(vec3));
    CAMERA_FRONT = (vec3*)malloc(sizeof(vec3));
    CAMERA_UP = (vec3*)malloc(sizeof(vec3));
    yaw = (float*)malloc(sizeof(float));
    pitch = (float*)malloc(sizeof(float));

    if (!CAMERA_POS || !CAMERA_FRONT || !CAMERA_UP || !yaw || !pitch) {
        printf("FAILED TO ALLOCATE CAMERA VARS. \n");
        exit(1);
    }

    glm_vec3_copy(camera_pos, *CAMERA_POS);
    glm_vec3_copy(camera_front, *CAMERA_FRONT);
    glm_vec3_copy(camera_up, *CAMERA_UP);

    *yaw = -90.0f;
    *pitch = 0.0f;
}

void update_camera(mat4 view_mat) {
    // CAMERA_FRONT direction
    vec3 direction;
    direction[0] = cos(glm_rad(*yaw)) * cos(glm_rad(*pitch)); // x
    direction[1] = sin(glm_rad(*pitch)); // y
    direction[2] = sin(glm_rad(*yaw)) * cos(glm_rad(*pitch)); // z
    glm_normalize(direction);
    glm_vec3_copy(direction, *CAMERA_FRONT);
    
    // vec3 camera_dir;
    // glm_vec3_add(*CAMERA_POS, *CAMERA_FRONT, (float*)camera_dir);
    // glm_normalize(camera_dir);

    // vec3 world_up = {0.0f, 1.0f, 0.0f};
    // vec3 camera_right;
    // glm_cross(world_up, camera_dir, camera_right);
    // glm_normalize(camera_right);

    vec3 center;
    glm_vec3_add(*CAMERA_POS, *CAMERA_FRONT, center);
    
    glm_mat4_identity(view_mat);
    glm_lookat(*CAMERA_POS, center, *CAMERA_UP, view_mat);
}