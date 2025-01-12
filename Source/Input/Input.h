#pragma once
#include <iostream>
#include <glfw3.h>  

class Input
{
public:

	Input();

	static bool is_pressed(int key_code);
	static bool is_pressed(char key_value);

	static bool is_released(int key_code);
	static bool is_released(char key_value);


	static void set_window(GLFWwindow* window);

private:

	static GLFWwindow* window;
};

