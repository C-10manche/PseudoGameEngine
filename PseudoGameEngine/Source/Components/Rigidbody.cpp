#include "Rigidbody.h"

Rigidbody::Rigidbody() :	position(0), 
							velocity(0), 
							acceleration(0), 
							mass(1),
							restitution(1),
							use_gravity(true),
							is_static(false),
							collider(nullptr)
{

}

Rigidbody::	~Rigidbody() {

	delete collider;
}

void Rigidbody::add_force(Vec3f force) {
	acceleration += force;
}