#include <glad/glad.h>
#include <callbacks.h>
#include <stdbool.h>
#define CAMERA_VARS_H
#include "engine/camera.h"
#include "main.h"

int firstMouse = 1;
float lastX = 400, lastY = 300;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	if (firstMouse == 1)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = 0;
    }
	
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	*yaw += xoffset;
	*pitch += yoffset;

	if(*pitch > 89.0f)
        *pitch = 89.0f;
    if(*pitch < -89.0f)
        *pitch = -89.0f;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void processInputs(GLFWwindow *window) {
	const float cameraSpeed = 3.2f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		vec3 cam_front_scaled;
		glm_vec3_scale(*CAMERA_FRONT, cameraSpeed, cam_front_scaled);
		glm_vec3_add(*CAMERA_POS, cam_front_scaled, *CAMERA_POS);
	}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		vec3 cam_front_scaled;
		glm_vec3_scale(*CAMERA_FRONT, cameraSpeed, cam_front_scaled);
		glm_vec3_sub(*CAMERA_POS, cam_front_scaled, *CAMERA_POS);
	}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		vec3 cam_right;
		glm_cross(*CAMERA_FRONT, *CAMERA_UP, cam_right);
		glm_normalize(cam_right);
		vec3 cam_right_scaled;
		glm_vec3_scale(cam_right, cameraSpeed, cam_right_scaled);
		glm_vec3_sub(*CAMERA_POS, cam_right_scaled, *CAMERA_POS);
	}
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		vec3 cam_right;
		glm_cross(*CAMERA_FRONT, *CAMERA_UP, cam_right);
		glm_normalize(cam_right);
		vec3 cam_right_scaled;
		glm_vec3_scale(cam_right, cameraSpeed, cam_right_scaled);
		glm_vec3_add(*CAMERA_POS, cam_right_scaled, *CAMERA_POS);
	}
}
