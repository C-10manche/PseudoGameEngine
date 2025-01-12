#include "Scene.h"
#include "../GameObject/GameObject.h"

#include <glfw3.h>  

Scene::Scene(GLFWwindow* _window) : is_running(false), window(_window)
{

}

Scene::~Scene()
{
	for (GameObject* game_object : game_objects) {
		delete game_object;
	}
}

void Scene::ready()
{
	for (GameObject* game_object : game_objects)
	{
		game_object->ready();
	}

	this->is_running = true;
}

void Scene::init() { }

void Scene::update(float delta_time) { }

void Scene::add_game_object(GameObject* game_object)
{
		game_objects.push_back(game_object);
}
