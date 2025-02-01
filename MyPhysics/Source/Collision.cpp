#include "Collision.h"
#include "Body.h"
#include "Shape.h"
#include "SphereShape.h"
#include "MeshShape.h"
#include "Vec3f.h"
#include "MathHelper.h"

#include <iostream>
#include <limits>
#include <vector>
#include <array>

void Collision::resolve_collision(Body* body_a, Body* body_b) {


	if (body_a->is_static && body_b->is_static) {
		return;
	}

	if (body_a->shape == nullptr || body_b->shape == nullptr) {
		return;
	}

	if (SphereShape* shape_a = dynamic_cast<SphereShape*>(body_a->shape)) {
		if (SphereShape* shape_b = dynamic_cast<SphereShape*>(body_b->shape)) {
			resolve_collision_sphere_to_sphere(body_a, body_b, shape_a, shape_b);
		}

		if (MeshShape* shape_b = dynamic_cast<MeshShape*>(body_b->shape)) {
			resolve_collision_sphere_to_mesh(body_a, body_b, shape_a, shape_b);
		}
	}


	if (MeshShape* shape_a = dynamic_cast<MeshShape*>(body_a->shape)) {
		if (SphereShape* shape_b = dynamic_cast<SphereShape*>(body_b->shape)) {
			resolve_collision_sphere_to_mesh(body_a, body_b, shape_b, shape_a);
		}

		// TODO : mesh to mesh collision resolution
	}
}

void Collision::resolve_collision_sphere_to_sphere(Body* sphere_body_a, Body* sphere_body_b, SphereShape* sphere_shape_a, SphereShape* sphere_shape_b) {
	
	Vec3f normal;
	float depth = 0;

	if (sphere_2_sphere_intersect(sphere_body_a->position, sphere_body_b->position, sphere_shape_a->radius, sphere_shape_b->radius, normal, depth)) {
		seperate_bodies(sphere_body_a, sphere_body_b, normal, depth);
		resolve_collision_dynamic(sphere_body_a, sphere_body_b, normal);
	}
}

void Collision::resolve_collision_sphere_to_mesh(Body* sphere_body, Body* mesh_body, SphereShape* sphere_shape, MeshShape* mesh_shape) {

	Vec3f normal;
	float depth;

	const std::vector<unsigned int>& indices = mesh_shape->indices;
	const std::vector<std::array<float, 3>>& vertices = mesh_shape->vertices;// mesh_shape->get_transformed_vertices(mesh_body->position, mesh_body->rotation);

	for (int i = 0; i < indices.size(); i += 3) {
		unsigned int vertex1_index = indices[i];
		unsigned int vertex2_index = indices[i + 1];
		unsigned int vertex3_index = indices[i + 2];


		Vec3f vertex1(vertices[vertex1_index][0], vertices[vertex1_index][1], vertices[vertex1_index][2]);
		Vec3f vertex2(vertices[vertex2_index][0], vertices[vertex2_index][1], vertices[vertex2_index][2]);
		Vec3f vertex3(vertices[vertex3_index][0], vertices[vertex3_index][1], vertices[vertex3_index][2]);

		if (sphere_2_triangle_intersect(sphere_body->position, vertex1, vertex2, vertex3, sphere_shape->radius, normal, depth)) {
			seperate_bodies(sphere_body, mesh_body, normal, depth);
			resolve_collision_dynamic(sphere_body, mesh_body, normal);
		}
	}
}

void Collision::seperate_bodies(Body* body_a, Body* body_b, Vec3f normal, float depth) {
	if (body_a->is_static) {

		body_b->position += normal * depth;
	}
	else if (body_b->is_static) {

		body_a->position -= normal * depth;
	}
	else {

		body_a->position -= normal * depth / 2;
		body_b->position += normal * depth / 2;
	}
}

void Collision::resolve_collision_dynamic(Body* body_a, Body* body_b, Vec3f collision_normal) {

	Vec3f relative_velocity = body_b->velocity - body_a->velocity;
	if (relative_velocity.dot(collision_normal) > 0) {
		return;
	}

	// coefficient of restitution
	float e = min(body_a->restitution, body_b->restitution);

	if (body_a->is_static) {
		Vec3f vb_along_normal = collision_normal * body_b->velocity.dot(collision_normal);
		Vec3f vb_along_tangent = body_a->velocity - vb_along_normal;

		body_b->velocity = -vb_along_normal * e + vb_along_tangent;
	}
	else if (body_b->is_static) {
		Vec3f va_along_normal = collision_normal * body_a->velocity.dot(collision_normal);
		Vec3f va_along_tangent = body_a->velocity - va_along_normal;

		body_a->velocity = -va_along_normal * e + va_along_tangent;
	}
	else {
		Vec3f va_along_normal = collision_normal * body_a->velocity.dot(collision_normal);
		Vec3f vb_along_normal = collision_normal * body_b->velocity.dot(collision_normal);

		Vec3f va_along_tangent = body_a->velocity - va_along_normal;
		Vec3f vb_along_tangent = body_b->velocity - vb_along_normal;

		float ma = body_a->mass;
		float mb = body_b->mass;

		Vec3f va_final_along_normal = (va_along_normal * (ma - e * mb) + vb_along_normal * mb * (1 + e)) / (ma + mb);
		Vec3f vb_final_along_normal = (vb_along_normal * (mb - e * ma) + va_along_normal * ma * (1 + e)) / (ma + mb);

		body_a->velocity = va_final_along_normal + va_along_tangent;
		body_b->velocity = vb_final_along_normal + vb_along_tangent;
	}

}

bool Collision::sphere_2_sphere_intersect(Vec3f position_a, Vec3f position_b, float radius_a, float radius_b, Vec3f& normal, float& depth) {
	float radii = radius_a + radius_b;
	float radii_sqr = radii * radii;

	Vec3f a_to_b = position_b - position_a;

	float distance_sqr = a_to_b.sqr_magnitude();
		
	if (distance_sqr <= radii_sqr) {
		normal = a_to_b.normalized();
		depth = radii - a_to_b.magnitude();

		return true;
	}

	return false;
}

bool Collision::sphere_2_triangle_intersect(Vec3f sphere_position, Vec3f triangle_point_a, Vec3f triangle_point_b, Vec3f triangle_point_c, float sphere_radius, Vec3f& normal, float& depth) {

	Vec3f closest_point = closest_point_on_triangle(sphere_position, triangle_point_a, triangle_point_b, triangle_point_c);
	Vec3f sphere_pos_to_point = closest_point - sphere_position;

	float distance_sqr = sphere_pos_to_point.sqr_magnitude();

	if (distance_sqr <= sphere_radius * sphere_radius) {
		normal = sphere_pos_to_point.normalized();
		depth = sphere_radius - sphere_pos_to_point.magnitude();

		return true;
	}

	return false;
}

Vec3f Collision::closest_point_on_triangle(Vec3f point, Vec3f triangle_point_a, Vec3f triangle_point_b, Vec3f triangle_point_c) {

	point = closest_point_on_plane(point, triangle_point_a, triangle_point_b, triangle_point_c);

	if (point_inside_triangle(point, triangle_point_a, triangle_point_b, triangle_point_c)) {
		return point;
	}

	Vec3f closest_point_on_edge_ab = closest_point_on_segment(point, triangle_point_a, triangle_point_b);
	Vec3f closest_point_on_edge_bc = closest_point_on_segment(point, triangle_point_b, triangle_point_c);
	Vec3f closest_point_on_edge_ca = closest_point_on_segment(point, triangle_point_c, triangle_point_a);

	float distance1 = (closest_point_on_edge_ab - point).sqr_magnitude();
	float distance2 = (closest_point_on_edge_bc - point).sqr_magnitude();
	float distance3 = (closest_point_on_edge_ca - point).sqr_magnitude();

	if (distance1 < distance2)
		return distance1 < distance3 ? closest_point_on_edge_ab : closest_point_on_edge_ca;

	return distance2 < distance3 ? closest_point_on_edge_bc : closest_point_on_edge_ca;
}

Vec3f Collision::closest_point_on_plane(Vec3f point, Vec3f plane_point_a, Vec3f plane_point_b, Vec3f plane_point_c) {

	Vec3f a_to_b = plane_point_b - plane_point_a;
	Vec3f a_to_c = plane_point_c - plane_point_a;
	Vec3f plane_normal = a_to_b.cross(a_to_c).normalized();

	float plane_distance_from_origin = plane_normal.dot(plane_point_a);

	float point_distance_from_plane = plane_normal.dot(point) - plane_distance_from_origin;

	return point - plane_normal * point_distance_from_plane;
}

bool Collision::point_inside_triangle(Vec3f point, Vec3f triangle_point_a, Vec3f triangle_point_b, Vec3f triangle_point_c) {

	triangle_point_a -= point;
	triangle_point_b -= point;
	triangle_point_c -= point;

	Vec3f bc_cross = triangle_point_b.cross(triangle_point_c);
	Vec3f ca_cross = triangle_point_c.cross(triangle_point_a);
	Vec3f ab_cross = triangle_point_a.cross(triangle_point_b);

	return bc_cross.dot(ca_cross) >= 0.0f && bc_cross.dot(ab_cross) >= 0.0f;
}

Vec3f Collision::closest_point_on_segment(Vec3f point, Vec3f line_point_a, Vec3f line_point_b) {

	Vec3f a_to_b = line_point_b - line_point_a;

	float t = a_to_b.dot(point) / a_to_b.sqr_magnitude();

	t = clamp(t, 0, 1);

	return line_point_a + a_to_b * t;
}
