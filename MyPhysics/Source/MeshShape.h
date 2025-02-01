#pragma once

#include "Shape.h"
#include "Vec3f.h"
#include "Quaternion.h"

#include <array>
#include <vector>

class MeshShape : public Shape
{
public:

	std::vector<std::array<float, 3>> vertices;
	std::vector<unsigned int> indices;

	MeshShape();

	std::vector<std::array<float, 3>> get_transformed_vertices(Vec3f position, Quaternion rotation);
};

