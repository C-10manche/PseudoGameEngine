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
};

