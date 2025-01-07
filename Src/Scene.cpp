#include "Scene.h"
#include "GameObject.h"

Scene::Scene() : is_running(false)
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
