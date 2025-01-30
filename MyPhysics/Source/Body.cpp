#include "Body.h"
#include "Vec3f.h"

Body::Body() :	position(0), 
				velocity(0), 
				acceleration(0), 
				use_gravity(true),
				is_static(false),
				shape(nullptr)
{

}

Body::~Body() {
	delete shape;
}

void Body::add_force(Vec3f force) {
	acceleration += force;
}

void Body::step(float delta_time) {
	
	if (is_static) {
		return;
	}

	velocity += acceleration * delta_time;
	position += velocity * delta_time;

	acceleration = Vec3f::ZERO();
}