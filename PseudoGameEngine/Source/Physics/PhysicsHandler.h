#pragma once

#include <unordered_map>

class PhysicsWorld;
class Body;
class Rigidbody;

class PhysicsHandler {
public:
	PhysicsWorld* physics_world;
	std::unordered_map<Rigidbody*, Body*> rigibody_to_body_map;

	PhysicsHandler();

	void add_rigidbody(Rigidbody* rigidbody);

	void step(float delta_time);

	void set_gravity_force(float force);

	float get_gravity_force();

	void sync_rigidbody_to_body();

	void sync_body_to_rigidbody();

	void sync_transform_to_rigidbody();

	void sync_rigidbody_to_transform();

private:
};