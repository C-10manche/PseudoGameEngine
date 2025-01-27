#include "Component.h"

Component::Component() : game_object(nullptr) {
	
}


Component::~Component() { }

void Component::ready() { }

void Component::update(float delta_time) { }
