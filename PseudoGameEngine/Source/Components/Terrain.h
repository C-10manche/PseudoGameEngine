#pragma once

#include "Component.h"
#include "../Render/Mesh.h"

class Terrain : public Component {
public:
	float width;
	float height;

	void ready() override;
	void update (float delta_time) override;

	// add meshrenderer to gameobject parent
};

