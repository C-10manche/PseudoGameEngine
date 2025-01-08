#pragma once
#include <iostream>
#include <string>	 
#include <vector> 

class GameObject;

class Scene {

public:

	std::vector<GameObject*> game_objects;

	bool is_running;

	Scene();
	~Scene();

	virtual void init();

	void ready();

	virtual void update(float delta_time);

	void add_game_object(GameObject* game_object);
};