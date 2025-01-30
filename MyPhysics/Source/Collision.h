#pragma once

#include "Body.h"
#include "Vec3f.h"

#include <array>

class Collision
{
public:
	
	static bool intersect(Body* body_a, Body* body_b, Vec3f& normal, float& depth);

	static bool sphere_2_sphere_intersect(Vec3f position_a, Vec3f position_b, float radius_a, float radius_b, Vec3f& normal, float& depth);

	static bool sphere_2_triangle_intersect(Vec3f sphere_position, std::array<float, 3> triangle_points, float sphere_radius, Vec3f& normal, float& depth);
};

