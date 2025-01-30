#include "PhysicsHandler.h"
#include "PhysicsWorld.h"
#include "Body.h"
#include "../Components/Rigidbody.h"
#include "../Components/Transform.h"
#include "../GameObject/GameObject.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "Shape.h"
#include "SphereShape.h"

PhysicsHandler::PhysicsHandler() {
	this->physics_world = new PhysicsWorld();
}

void PhysicsHandler::add_rigidbody(Rigidbody* rigidbody) {
	
	Body* body = this->physics_world->add_body();
	if (Collider* collider = rigidbody->collider) {
		if (SphereCollider* sphere_collider = dynamic_cast<SphereCollider*>(collider)) {
			SphereShape* sphere_shape = new SphereShape();
			sphere_shape->radius = sphere_collider->radius;
			body->shape = sphere_shape;
		}
	}

	rigibody_to_body_map[rigidbody] = body;
}

void PhysicsHandler::step(float delta_time) {

	this->sync_body_to_rigidbody();

	this->physics_world->step(delta_time);

	this->sync_rigidbody_to_body();

	this->sync_transform_to_rigidbody();
}

void PhysicsHandler::sync_rigidbody_to_body() {

	for (auto& pair : rigibody_to_body_map) {
		pair.first->position = pair.second->position;
		pair.first->velocity = pair.second->velocity;
		pair.first->acceleration = pair.second->acceleration;
	}
}

void PhysicsHandler::sync_body_to_rigidbody() {

	for (auto& pair : rigibody_to_body_map) {
		pair.second->position = pair.first->position;
		pair.second->velocity = pair.first->velocity;
		pair.second->acceleration = pair.first->acceleration;
		pair.second->use_gravity = pair.first->use_gravity;
		pair.second->is_static = pair.first->is_static;
	}
}

void PhysicsHandler::sync_transform_to_rigidbody() {

	for (auto& pair : rigibody_to_body_map) {
		Transform* transform = pair.first->game_object->transform;
		transform->position = pair.first->position;
	}
}

void PhysicsHandler::sync_rigidbody_to_transform() {

	for (auto& pair : rigibody_to_body_map) {
		Transform* transform = pair.first->game_object->transform;
		pair.first->position = transform->position ;
	}
}

void PhysicsHandler::set_gravity_force(float force) {
	physics_world->gravity_force = force;
}


float PhysicsHandler::get_gravity_force() {
	return physics_world->gravity_force;
}
