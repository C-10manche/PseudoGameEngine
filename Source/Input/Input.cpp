#include "Input.h"
#include <glfw3.h>  
#include "../Utils/MyMath.h"

GLFWwindow* Input::window = nullptr;


Input::Input() {
}

void Input::set_window(GLFWwindow* window)
{
	Input::window = window;
}

void Input::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    //if (firstMouse)
    //{
    //    lastX = xpos;
    //    lastY = ypos;
    //    firstMouse = false;
    //}

    //mouse_x = xpos - lastX;
    //mouse_y = lastY - ypos; // reversed since y-coordinates go from bottom to top
    //lastX = xpos;
    //lastY = ypos;

}

bool Input::is_pressed(char key_value) {
	char new_key = toupper(key_value);
	int key_code = (int)key_value;
	if (glfwGetKey(window, key_code) == GLFW_PRESS) { 
		return true;
	}
	return false;
}

bool Input::is_pressed(int key_code) {
	if (glfwGetKey(window, key_code) == GLFW_PRESS) {
		return true;
	}
	return false;
}

bool Input::is_released(char key_value) {
	int key_code = (int)key_value;
	if (glfwGetKey(window, key_code) == GLFW_RELEASE) {
		return true;
	}
	return false;
}

bool Input::is_released(int key_code) {
	if (glfwGetKey(window, key_code) == GLFW_RELEASE) {
		return true;
	}
	return false;
}

