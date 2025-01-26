#pragma once

#include "MyMath.h"
class Quaternion
{
public:

	float w;
	Vec3f v;

	Quaternion();
	Quaternion(float _w, Vec3f _v);
	Quaternion(const Vec3f& _axis, float _angle, bool _alrdy_in_rad = false);

	Quaternion conjugate();

	Vec3f rotate(Vec3f _v);

	Mat4f get_rotation_matrix();

	Quaternion operator*(const Quaternion& _quat) const;
	Quaternion operator*(const Vec3f& _v) const;
};

