#pragma once

#include "Collider.h"
#include <array>
#include <vector>

class MeshCollider : public Collider
{
public:

	std::vector<std::array<float, 3>> vertices;
	std::vector<unsigned int> indices;

	MeshCollider();
};

