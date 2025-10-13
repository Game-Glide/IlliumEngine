#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <callbacks.h>
#include <draw_calls.h>
#include <stdio.h>

int main() {
	printf("creating window");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Stuff", NULL, NULL);
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

	initialization();

	while (!glfwWindowShouldClose(window)) {
		processInputs(window);

		clearBufferGreen();
		drawObjects();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cleanup();
	glfwTerminate();
	return 0;
}
