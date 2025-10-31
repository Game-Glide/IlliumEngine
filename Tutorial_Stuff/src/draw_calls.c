#include <draw_calls.h>
#include <util/shader.h>
#include <util/constants.h>
#include <glad/glad.h>
#include <stb_image.h>
#include <GLFW/glfw3.h>
#include <string.h>

#include <cglm/cglm.h>

Shader* _defaultShader = NULL;
float* mixFactor = NULL;

void clearBufferGreen() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void initialization() {
    // WIREFRAME MODE
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

#pragma region Load Textures

    unsigned int texture1;
    glGenTextures(1, &texture1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    char filepath1[1024];
    snprintf(filepath1, sizeof(filepath1), "%stextures/container.jpg", RESOURCE_DIR);
    unsigned char* data = stbi_load(filepath1, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("Failed to load texture\n");
    }
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    char filepath2[512];
    snprintf(filepath2, sizeof(filepath2), "%stextures/awesomeface.png", RESOURCE_DIR);
    unsigned char* data1 = stbi_load(filepath2, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("Failed to load texture\n");
    }
    stbi_image_free(data1);
#pragma endregion


#pragma region Shader Creation
    Shader* defaultShader = malloc(sizeof(Shader));
    create_shader(defaultShader, "defaultVert.glsl", "defaultFrag.glsl");
    mat4 trans;
    glm_mat4_identity(trans);
    glm_rotate(trans, glm_rad(90.0f), (vec3) {0.0f, 0.0f, 1.0f});
    glm_scale(trans, (vec3) {0.5f, 0.5f, 0.5f});

    use_shader(defaultShader);
    set_shader_int(defaultShader, "texture1", 0);
    set_shader_int(defaultShader, "texture2", 1);
    mixFactor = malloc(sizeof(float));
    *mixFactor = 0.2f;
    set_shader_float(defaultShader, "mixFactor", *mixFactor);

    _defaultShader = defaultShader;
#pragma endregion

#pragma region Vertex Initialization
    float vertices[] = { // vertex positions in local space
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
#pragma endregion
}

void drawObjects() {
    vec3 cubePositions[] = { // cube positions in world space
        { 2.0f,  5.0f, -15.0f },
        { 0.0f,  0.0f,  0.0f  },
        {-1.5f, -2.2f, -2.5f  },
        {-3.8f, -2.0f, -12.3f },
        { 2.4f, -0.4f, -3.5f  },
        {-1.7f,  3.0f, -7.5f  },
        { 1.3f, -2.0f, -2.5f  },
        { 1.5f,  2.0f, -2.5f  },
        { 1.5f,  0.2f, -1.5f  },
        {-1.3f,  1.0f, -1.5f  }
    };
    *mixFactor = sin((float)glfwGetTime())/2;
    set_shader_float(_defaultShader, "mixFactor", *mixFactor);

    mat4 view; // View matrix - world space to eye space
    mat4 projection; // Projection matrix - eye space to clip space

    glm_mat4_identity(view);
    glm_translate(view, (vec3) {0.0f, 0.0f, -3.0f});

    glm_mat4_identity(projection);
    glm_perspective(glm_rad(45.0f), (float)800/(float)600, 0.1f, 100.0f, projection);

    // Send to shader
    set_shader_matrix_4fv(_defaultShader, "view", view);
    set_shader_matrix_4fv(_defaultShader, "projection", projection);

    for (int i = 0; i < 10; i++) {
        mat4 model; // Model matrix - local to world space

        glm_mat4_identity(model);
        glm_translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        glm_rotate(model, glm_rad(angle),(vec3) {1.0f, 0.3f, 0.5f});

        if (i % 3 == 0 || i == 0) {
            glm_rotate(model, (float)glfwGetTime(), (vec3) {1.0f, 0.3f, 0.5f});
        }

        // Send to shader
        set_shader_matrix_4fv(_defaultShader, "model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void cleanup() {
    free(_defaultShader);
    free(mixFactor);
}
