#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <callbacks.h>
#include <draw_calls.h>
#include <stdio.h>
#include "main.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
	printf("creating window\n");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL_Engine", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
	return -1;
}

	glfwMakeContextCurrent(window);
	
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return -1;
	}
	
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	initialization();

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInputs(window);

		clearBufferGreen();
		drawObjects(); // TODO: make an actual render loop

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cleanup();
	glfwTerminate();
	return 0;
}