#pragma once

#include "../Utils/MyMath.h"
#include "Transform.h"
#include "Component.h"

#include <glfw3.h>  

class Camera : public Component{
public:

	enum class Projection {
		orthographic,
		perspective,
	};

	Projection projection_type;

	GLFWwindow* window;

	float fov;
	float near;
	float far;

	Camera();

	void update(float delta_time);
	Mat4f get_rotation_matrix();
	Mat4f get_translation_matrix();
	Mat4f get_view_matrix();
	Mat4f get_perspective_matrix();
};

