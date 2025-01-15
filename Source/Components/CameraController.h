#pragma once

#include "../Input/Input.h"
#include "../Utils/MyMath.h"
#include "Transform.h"
#include "Component.h"

class CameraController : public Component
{
public:
	float speed;

	void ready() override;

	void update(float delta_time) override;

	void handle_movements(float delta_time);
};

