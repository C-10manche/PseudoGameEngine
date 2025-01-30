#pragma once

#include "MathHelper.h"
#include "Transform.h"
#include "Component.h"

class Camera : public Component{
public:

	enum class Projection {
		orthographic,
		perspective,
	};

	Projection projection_type;

	float fov;
	float near;
	float far;

	Camera();

	void update(float delta_time);
	Mat4f get_rotation_matrix();
	Mat4f get_translation_matrix();
	Mat4f get_view_matrix();
	Mat4f get_perspective_matrix(float aspect_ratio);
};

