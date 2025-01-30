#include "Collision.h"
#include "Body.h"
#include "Shape.h"
#include "SphereShape.h"
#include "Vec3f.h"

bool Collision::intersect(Body* body_a, Body* body_b, Vec3f& normal, float& depth) {
	
	Shape* shape_a = body_a->shape;
	Shape* shape_b = body_b->shape;

	if (shape_a == nullptr || shape_b == nullptr) {
		return false;
	}

	if (SphereShape* sphere_shape_a = dynamic_cast<SphereShape*>(shape_a)) {
		if (SphereShape* sphere_shape_b = dynamic_cast<SphereShape*>(shape_b)) {
			return sphere_2_sphere_intersect(body_a->position, body_b->position, sphere_shape_a->radius, sphere_shape_b->radius, normal, depth);
		}
	}

	return false;
}

bool Collision::sphere_2_sphere_intersect(Vec3f position_a, Vec3f position_b, float radius_a, float radius_b, Vec3f& normal, float& depth) {
	float radii = radius_a + radius_b;
	float radii_sqr = radii * radii;

	Vec3f from_a_to_b = position_b - position_a;

	float distance_sqr = from_a_to_b.sqr_magnitude();
		
	if (distance_sqr <= radii_sqr) {
		normal = from_a_to_b.normalized();
		depth = radii - from_a_to_b.magnitude();

		return true;
	}

	return false;
}

bool Collision::sphere_2_triangle_intersect(Vec3f sphere_position, std::array<float, 3> triangle_points, float sphere_radius, Vec3f& normal, float& depth) {

	return false;
}
