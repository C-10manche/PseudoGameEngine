#pragma once

#include "Shape.h"

#include <array>
#include <vector>

class MeshShape : public Shape
{
public:

	std::vector<std::array<float, 3>> vertices;
	std::vector<unsigned int> indices;

	MeshShape();
};

