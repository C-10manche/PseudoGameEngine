#pragma once
#include <iostream>
#include <glfw3.h>  
#include <array>

class Input
{
public:
    static bool firstMouse;
	static GLFWwindow* window;
	static float lastX;
	static float lastY;

	Input();

	static bool is_pressed(int key_code);
	static bool is_pressed(char key_value);

	static bool is_released(int key_code);
	static bool is_released(char key_value);

	static std::array<float, 2> get_mouse_delta();

	static void set_window(GLFWwindow* window);
};

