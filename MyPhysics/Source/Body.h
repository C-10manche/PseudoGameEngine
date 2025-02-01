#pragma once

#include "Vec3f.h"
#include "Quaternion.h"
#include "Shape.h"

class Body
{
public:
	Vec3f position;
	Quaternion rotation;
	Vec3f velocity;
	Vec3f acceleration;
	float mass;
	float restitution;
	bool use_gravity;
	bool is_static;

	Shape* shape;

	Body();
	~Body();

	void add_force(Vec3f force);
	void step(float delta_time);
};

