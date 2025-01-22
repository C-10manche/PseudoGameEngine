#pragma once

#include "MyMath.h"
class Quaternion
{
public:

	float w;
	Vec3f v;

	Quaternion() {};
	Quaternion(const Vec3f& _axis, float _angle, bool _alrdy_in_rad = false);

	Quaternion conjugated();

	Quaternion operator*(const Vec3f& _vec3f) const;
	Quaternion operator*(const Quaternion& _quat) const;



};

