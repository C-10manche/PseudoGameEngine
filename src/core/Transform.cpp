#include "Transform.h"

Transform::Transform() : position(Vec3f()), rotation(Vec3f()), scale(Vec3f()) {
}

Transform::Transform(Vec3f _position, Vec3f _rotation, Vec3f _scale)
{
	this->position = _position;
	this->rotation = _rotation;
	this->scale = _scale;
}
