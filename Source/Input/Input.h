#pragma once
#include <iostream>
#include <glfw3.h>  

class Input
{
public:
    static bool firstMouse;
	static float mouse_x;
	static float mouse_y;
	static GLFWwindow* window;
	static float lastX;
	static float lastY;

	Input();

	static bool is_pressed(int key_code);
	static bool is_pressed(char key_value);

	static bool is_released(int key_code);
	static bool is_released(char key_value);

	static bool is_mouse_in_motion();


	static void set_window(GLFWwindow* window);

	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

};

