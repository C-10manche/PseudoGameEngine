#pragma once

#include "core/Scene.h"

class TestScene : public Scene {
public:
	void init() override;
	void update(float delta_time) override;
};

