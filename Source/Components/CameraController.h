#pragma once

#include "../Input/Input.h"
#include "../Utils/MyMath.h"
#include "Transform.h"
#include "Component.h"

class CameraController : public Component
{
public:
	float speed;
	float sensitivity;
	float yaw, pitch;

	CameraController();

	void ready() override;

	void update(float delta_time) override;

	void handle_movement(float delta_time);
	void handle_orientation(float delta_time);

};

