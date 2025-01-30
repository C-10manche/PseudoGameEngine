#pragma once
#include <iostream>
#include <string>	 
#include <vector> 

#include "../Components/Camera.h"
#include "../Render/Material.h"
#include "../Render/Shader.h"
#include "../Physics/PhysicsHandler.h"


struct GLFWwindow;
class GameObject;
class PhysicsWorld;

class Scene {

public:

	GLFWwindow* window;
	Camera* main_camera;

	PhysicsHandler* physics_handler;

	std::vector<GameObject*> game_objects;

	std::unordered_map<std::string, Shader*> shaders;
	Material* defaultMaterial;

	bool is_running;

	Scene();
	~Scene();

	void set_window(GLFWwindow* _window);

	virtual void init();

	void ready();

	void update(float delta_time);

	void add_game_object(GameObject* game_object);

	GameObject* create_sphere(const std::string& name = "Sphere");

	GameObject* create_cube(const std::string& name = "Cube");

	GameObject* create_capsule(const std::string& name = "Capsule");

	Camera* create_camera();
};