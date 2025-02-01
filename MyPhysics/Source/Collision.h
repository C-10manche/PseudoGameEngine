#pragma once

#include "Body.h"
#include "SphereShape.h"
#include "MeshShape.h"
#include "Vec3f.h"

#include <vector>
#include <array>

class Collision
{
public:

	static void resolve_collision(Body* body_a, Body* body_b);

	static void resolve_collision_sphere_to_sphere(Body* sphere_body_a, Body* sphere_body_b, SphereShape* sphere_shape_a, SphereShape* sphere_shape_b);
	
	static void resolve_collision_sphere_to_mesh(Body* sphere_body, Body* mesh_body, SphereShape* sphere_shape, MeshShape* mesh_shape);

	static void seperate_bodies(Body* body_a, Body* body_b, Vec3f normal, float depth);

	static void resolve_collision_dynamic(Body* body_a, Body* body_b, Vec3f collision_normal);
	
	static bool sphere_2_sphere_intersect(Vec3f position_a, Vec3f position_b, float radius_a, float radius_b, Vec3f& normal, float& depth);

	static bool sphere_2_triangle_intersect(Vec3f sphere_position, Vec3f triangle_point_a, Vec3f triangle_point_b, Vec3f triangle_point_c, float sphere_radius, Vec3f& normal, float& depth);

	static Vec3f closest_point_on_plane(Vec3f point, Vec3f plane_point_a, Vec3f plane_point_b, Vec3f plane_point_c);

	static Vec3f closest_point_on_triangle(Vec3f point, Vec3f triangle_point_a, Vec3f triangle_point_b, Vec3f triangle_point_c);

	static Vec3f closest_point_on_segment(Vec3f point, Vec3f line_point_a, Vec3f line_point_b);

	static bool point_inside_triangle(Vec3f point, Vec3f triangle_point_a, Vec3f triangle_point_b, Vec3f triangle_point_c);

};

