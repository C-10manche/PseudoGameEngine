#include "Input.h"
#include <glfw3.h>  
#include "../Utils/MyMath.h"
#include <iomanip>

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

std::array<float, 2> Input::get_mouse_delta() {

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	float x = static_cast<float>(xpos);
	float y = static_cast<float>(ypos);

	if (firstMouse) {
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	float delta_x = x - lastX;
	float delta_y = y - lastY;

	lastX = x;
	lastY = y;

	return { delta_x, delta_y };
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

