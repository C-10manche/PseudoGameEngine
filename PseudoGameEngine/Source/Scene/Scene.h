#pragma once
#include <iostream>
#include <string>	 
#include <vector> 

#include <glad/glad.h>
#include <glfw3.h>

class GameObject;

class Scene {

public:

	std::vector<GameObject*> game_objects;
	GLFWwindow* window;

	bool is_running;

	Scene();
	virtual ~Scene();

	virtual void init();

	void ready();

	virtual void update(float delta_time);

	void add_game_object(GameObject* game_object);

	void set_window(GLFWwindow* _window);
};