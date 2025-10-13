#ifndef SHADER_H
#define SHADER_H
#include <stdio.h>
#include <util/constants.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cglm/cglm.h>

typedef struct Shader {
    unsigned int program_ID;
    char* vertex_shader_code;
    char* fragment_shader_code;
} Shader;

void create_shader(Shader* shader, const char* vshader_name, const char* fshader_name);
void use_shader(Shader* shader);
void set_shader_bool(Shader* shader, const char* name, bool value);
void set_shader_float(Shader* shader, const char* name, float value);
void set_shader_int(Shader* shader, const char* name, int value);
void set_shader_matrix_4fv(Shader* shader, const char* name, mat4 value);

#endif