#include "Input.h"
#include <glfw3.h>  
#include "../Utils/MyMath.h"

float Input::mouse_x = 0.0f;
float Input::mouse_y = 0.0f;

GLFWwindow* Input::window = nullptr;
bool Input::firstMouse = true;
float Input::lastX = 0.0f;
float Input::lastY = 0.0f;


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

	if (firstMouse)
	{
		Input::lastX = xpos;
		Input::lastY = ypos;
		Input::firstMouse = false;
	}

	Input::mouse_x = xpos - Input::lastX;
	Input::mouse_y = Input::lastY - ypos;


	Input::lastX = xpos;
	Input::lastY = ypos;
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

bool Input::is_mouse_in_motion()
{
	if(Input::mouse_x != 0.0f || Input::mouse_y != 0.0f)
		return true;
	return false;
}

bool Input::is_released(int key_code) {
	if (glfwGetKey(window, key_code) == GLFW_RELEASE) {
		return true;
	}
	return false;
}

