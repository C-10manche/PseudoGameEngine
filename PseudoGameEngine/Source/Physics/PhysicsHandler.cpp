#include "PhysicsHandler.h"
#include "PhysicsWorld.h"
#include "Body.h"
#include "../Components/Rigidbody.h"
#include "../Components/Transform.h"
#include "../GameObject/GameObject.h"
#include "../Components/MeshRenderer.h"
#include "../Render/Mesh.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "MeshCollider.h"
#include "Shape.h"
#include "SphereShape.h"
#include "MeshShape.h"

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

		if (MeshCollider* mesh_collider = dynamic_cast<MeshCollider*>(collider)) {
			if (MeshRenderer* renderer = rigidbody->game_object->get_component<MeshRenderer>()) {
				if (Mesh* mesh = renderer->mesh) {
					body->shape = mesh_to_mesh_shape(mesh);
				}
			}
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
		pair.first->rotation = pair.second->rotation;
		pair.first->velocity = pair.second->velocity;
		pair.first->acceleration = pair.second->acceleration;
	}
}

void PhysicsHandler::sync_body_to_rigidbody() {

	for (auto& pair : rigibody_to_body_map) {
		pair.second->position = pair.first->position;
		pair.second->rotation = pair.first->rotation;
		pair.second->velocity = pair.first->velocity;
		pair.second->acceleration = pair.first->acceleration;
		pair.second->use_gravity = pair.first->use_gravity;
		pair.second->is_static = pair.first->is_static;
		pair.second->mass = pair.first->mass;
		pair.second->restitution = pair.first->restitution;
	}
}

void PhysicsHandler::sync_transform_to_rigidbody() {

	for (auto& pair : rigibody_to_body_map) {
		Transform* transform = pair.first->game_object->transform;
		transform->position = pair.first->position;
		transform->rotation = pair.first->rotation;
	}
}

void PhysicsHandler::sync_rigidbody_to_transform() {

	for (auto& pair : rigibody_to_body_map) {
		Transform* transform = pair.first->game_object->transform;
		pair.first->position = transform->position;
		pair.first->rotation = transform->rotation;
	}
}

void PhysicsHandler::set_gravity_force(float force) {
	physics_world->gravity_force = force;
}


float PhysicsHandler::get_gravity_force() {
	return physics_world->gravity_force;
}

MeshShape* PhysicsHandler::mesh_to_mesh_shape(Mesh* mesh) {
	MeshShape* mesh_shape = new MeshShape();
	for (const Vertex& v : mesh->vertices) {
		mesh_shape->vertices.push_back({ v.position[0], v.position[1], v.position[2] });
	}

	mesh_shape->indices = mesh->indices;

	return mesh_shape;
}
