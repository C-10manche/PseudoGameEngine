#pragma once

#include "Component.h"
#include "../Render/Mesh.h"

class Terrain : public Component {
public:

	Terrain();

	float size;
	int resolution;

	void ready() override;
	void update (float delta_time) override;

	// add meshrenderer to gameobject parent
};

