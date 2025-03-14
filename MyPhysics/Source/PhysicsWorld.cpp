#include "PhysicsWorld.h"
#include "Body.h"
#include "Vec3f.h"
#include "Collision.h"

#include <iostream>

PhysicsWorld::PhysicsWorld() : gravity_force(9.81f) {

}

PhysicsWorld::~PhysicsWorld() {

	for (Body* b : bodies) {
		delete b;
	}
}

Body* PhysicsWorld::add_body() {

	Body* body = new Body();

	bodies.push_back(body);

	return body;
}

void PhysicsWorld::remove_body(Body* body) {

	delete body;

	bodies.erase(std::remove(bodies.begin(), bodies.end(), body), bodies.end());
}

void PhysicsWorld::step(float delta_time) {

	// apply gravity
	for (Body* b : bodies) {
		if (b->use_gravity) {
			b->add_force(Vec3f::DOWN * gravity_force);
		}
	}

	// step
	for (Body* b : bodies) {
		b->step(delta_time);
	}

	// resolve_collision;
	for (int i = 0; i < bodies.size() - 1; i++) {
		Body* body_a = bodies[i];
		for(int j = i + 1; j < bodies.size(); j++) {
			Body* body_b = bodies[j];

			Collision::resolve_collision(body_a, body_b);
		}
	}
	 
}
