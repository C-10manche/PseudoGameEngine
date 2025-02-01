#pragma once
#include "Vec3f.h"
#include "Quaternion.h"
#include "Component.h"
#include "../Physics/Collider.h"

class Rigidbody: public Component {
public:

	Vec3f position;
	Quaternion rotation;
	Vec3f velocity;
	Vec3f acceleration;
	float mass;
	float restitution;
	bool use_gravity;
	bool is_static;

	Collider* collider;

	Rigidbody();
	~Rigidbody();

	void add_force(Vec3f force);
};

