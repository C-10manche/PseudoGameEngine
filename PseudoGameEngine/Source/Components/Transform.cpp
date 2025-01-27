#include "Transform.h"
#include "Vec3f.h"
#include <cmath>

Transform::Transform() : position(0.0f), rotation(), scale(1.0f) { }

Vec3f Transform::get_right() {
	return this->rotation.rotate(Vec3f::RIGHT());
}

Vec3f Transform::get_up() {
	return this->rotation.rotate(Vec3f::UP());
}

Vec3f Transform::get_forward() {
	return this->rotation.rotate(Vec3f::FORWARD());
}

Mat4f Transform::get_model_matrix() {
	Mat4f scale_matrix(
		this->scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, this->scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, this->scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Mat4f rotation_matrix = this->rotation.get_rotation_matrix();

	Mat4f translation_matrix(
		1.0f, 0.0f, 0.0f, this->position.x,
		0.0f, 1.0f, 0.0f, this->position.y,
		0.0f, 0.0f, 1.0f, this->position.z,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Mat4f model_matrix = translation_matrix * rotation_matrix * scale_matrix;

	return model_matrix;
}
