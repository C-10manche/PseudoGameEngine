#pragma once

#include <scene.h>

class TestScene : public Scene {
public:
	void init() override;
	void update(float delta_time) override;
};

