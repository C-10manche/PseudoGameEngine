#pragma once

#include "../Utils/MyMath.h"
#include "Transform.h"
#include "Component.h"
#include "../Input/Input.h"

#include <glfw3.h>  

class Camera : public Component{
public:

	enum class Projection {
		orthographic,
		perspective,
	};

	Projection projection_type;


	Mat4f perspective;

	float fov;

	Camera();

	void update(float delta_time);
	//void handle_input(float delta_time);
	Mat4f get_view_matrix();
};

