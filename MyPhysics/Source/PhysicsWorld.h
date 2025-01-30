#pragma once

#include "Body.h"
#include <vector>

class PhysicsWorld
{
public:
	std::vector<Body*> bodies;
	float gravity_force;

	PhysicsWorld();
	~PhysicsWorld();

	void step(float delta_time);

	Body* add_body();
	void remove_body(Body* body);

};

