#include "GameObject.h"
#include "../Components/Component.h"
#include "../Components/Transform.h"

GameObject::GameObject() {
	name = "Game Object";

	this->transform = add_component<Transform>();
}

GameObject::~GameObject() {

	for (Component* component : components) {
		delete component;
	}
}

void GameObject::ready() {

	for (Component* component : components) {
		component->ready();
	}
}

void GameObject::update(float delta_time) {

	for (Component* component : components) {
		component->update(delta_time);
	}
}


