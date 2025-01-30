#pragma once
#include "Vec3f.h"
#include "Component.h"
#include "../Physics/Collider.h"

class Rigidbody: public Component {
public:
	Rigidbody();
	~Rigidbody();

	Vec3f position;
	Vec3f velocity;
	Vec3f acceleration;
	bool use_gravity;
	bool is_static;

	Collider* collider;
};

