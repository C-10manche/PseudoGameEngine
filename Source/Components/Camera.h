#pragma once

#include "../Utils/MyMath.h"
#include "Transform.h"
#include "Component.h"

class Camera : public Component
{
public:

	enum class Projection {
		orthographic,
		perspective,
	};

	Projection projection_type;
	float fov;
	Transform transform;
	Vec3f up;
	Mat4f perspective;
	Mat4f projection;

	Camera();

};

