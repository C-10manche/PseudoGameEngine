#pragma once
#include <iostream>
#include <glfw3.h>  

class Input
{
public:
    /*static bool firstMouse;
    static float lastX;
    static float lastY;
	static float mouse_x;
	static float mouse_y;*/



	Input();

	static bool is_pressed(int key_code);
	static bool is_pressed(char key_value);

	static bool is_released(int key_code);
	static bool is_released(char key_value);


	static void set_window(GLFWwindow* window);

	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);


private:

	static GLFWwindow* window;
};

