#include "Camera.h"
#include "utils/MyMath.h"

Camera::Camera() {

	this->projection_type = Projection::orthographic;
	this->fov = 90.0f;
	this->transform = Transform();
	this->up = Vec3f(0.0, 1.0f, 0.0f);
}