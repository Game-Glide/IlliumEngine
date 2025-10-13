#include <util/shader.h>
#include <glad/glad.h>
#include <io/io.h>

void create_shader(Shader *shader, const char *vshader_name, const char *fshader_name) {
    // VERTEX SHADER COMPILATION
    int success;
    char infoLog[512];
    char v_filepath[512] = V_SHADER_DIR;
    strcat(v_filepath, vshader_name);
    shader->vertex_shader_code = read_file(v_filepath);
    unsigned int v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, &shader->vertex_shader_code, NULL);
    glCompileShader(v_shader);
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(v_shader, 512, NULL, infoLog);
        fprintf(stderr, "Failed to compile vertex shader: %s\n", infoLog);
    }

    // FRAGMENT SHADER COMPILATION
    char f_filepath[512] = F_SHADER_DIR;
    strcat(f_filepath, fshader_name);
    shader->fragment_shader_code = read_file(f_filepath);
    unsigned int f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader, 1, &shader->fragment_shader_code, NULL);
    glCompileShader(f_shader);
    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(f_shader, 512, NULL, infoLog);
        fprintf(stderr, "Failed to compile fragment shader: %s\n", infoLog);
    }

    shader->program_ID = glCreateProgram();
    glAttachShader(shader->program_ID, v_shader);
    glAttachShader(shader->program_ID, f_shader);
    glLinkProgram(shader->program_ID);

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);
}

void use_shader(Shader *shader) {
    glUseProgram(shader->program_ID);
}

void set_shader_bool(Shader* shader, const char *name, bool value) {
    unsigned int loc = glGetUniformLocation(shader->program_ID, name);
    glUniform1i(loc, value);
}

void set_shader_float(Shader* shader, const char* name, float value) {
    unsigned int loc = glGetUniformLocation(shader->program_ID, name);
    glUniform1f(loc, value);
}

void set_shader_int(Shader* shader, const char* name, int value) {
    unsigned int loc = glGetUniformLocation(shader->program_ID, name);
    glUniform1i(loc, value);
}

void set_shader_matrix_4fv(Shader* shader, const char* name, mat4 value) {
    unsigned int loc = glGetUniformLocation(shader->program_ID, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, (const float*)value);
}