#include "Transform.h"
#include "../Utils/MyMath.h"
#include <cmath>

Transform::Transform()
{
	position = Vec3f();
	rotation = Quaternion();
	scale = Vec3f();
	up = Vec3f();
	forward = Vec3f();
	right = Vec3f();
}
