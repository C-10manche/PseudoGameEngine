#pragma once
#include <iostream>
#include <string>	 
#include <vector>	

class Component;
class Transform;
class Scene;

class GameObject{

public:

	Scene* scene;
	std::string	name;
	std::vector<Component*> components;
	Transform* transform;

	GameObject();
	~GameObject();

	void ready();

	void update(float delta_time);

	
	template <typename T>
	T* add_component() {

		T* component = new T();
		components.push_back(component);

		static_cast<Component*>(component)->game_object = this;

		return component;
	}

	template <typename T>
	T* get_component() {

		for (Component* component : components) {
			if (T* result = dynamic_cast<T*>(component))
				return result;
		}

		return nullptr;
	}
};