#pragma once

#include <vector>
#include <string>


struct Vertex {
	float position[3];
};

class Mesh
{
public:

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	static Mesh* generate_cube_mesh();
	static Mesh* generate_plane_mesh(int x_size, int z_size);
	static Mesh* generate_uv_sphere_mesh(int segments, int rings);
	static Mesh* generate_capsule_mesh(int segments, int rings_per_hemisphere);
};

