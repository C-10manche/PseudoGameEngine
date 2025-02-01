#pragma once

#include "Components/Component.h"
#include "Components/Rigidbody.h"
#include "Components/Transform.h"

class PlayerController : public Component
{
public:

	Transform* transform;
	Rigidbody* rb;
	float yaw;
	float pitch;
	float sensitivity;

	PlayerController();

	void ready() override;
	void update(float delta_time) override;

	void handle_rotation();
	void handle_movement(float delta_time);
};

