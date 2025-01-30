#pragma once

#include "Components/Component.h"

class Rigidbody;
 
class BallController : public Component
{
public:

	Rigidbody* rb;

	BallController();

	void ready() override;

	void update(float delta_time) override;
};

