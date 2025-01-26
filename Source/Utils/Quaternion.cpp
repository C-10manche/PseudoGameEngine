#include "Quaternion.h"

#include "MyMath.h"

Quaternion::Quaternion() : w(1.0f), v(0.0f) { }

Quaternion::Quaternion(float _w, Vec3f _v) : w(_w), v(_v) { }

Quaternion::Quaternion(const Vec3f& _axis, float _angle, bool _alrdy_in_rad) {
	float rad_angle = _alrdy_in_rad ? _angle : deg_to_rad(_angle);

	this->w = cosf(rad_angle / 2.0f);
	this->v = _axis.normalized() * sinf(rad_angle / 2.0f);
}

Quaternion Quaternion::conjugate() {

	return Quaternion(this->w, this->v * -1);
}

Vec3f Quaternion::rotate(Vec3f _v) {
	Quaternion q(0, _v);

	Quaternion result = *this * q * this->conjugate();

	return result.v;
}

Mat4f Quaternion::get_rotation_matrix() {
	float x = this->v.x;
	float y = this->v.y;
	float z = this->v.z;
	return Mat4f(
		1.0f - 2 * y * y - 2 * z * z, 2 * x * y - 2 * w * z, 2 * x * z + 2 * w * y, 0,
		2 * x * y + 2 * w * z, 1.0f - 2 * x * x - 2 * z * z, 2 * y * z + 2 * w * x, 0,
		2 * x * z - 2 * w * y, 2 * y * z + 2 * w * x, 1 - 2 * x * x - 2 * y * y, 0,
		0, 0, 0, 1);
}

Quaternion Quaternion::operator*(const Quaternion& _quat) const {

	Vec3f cross = this->v.cross(_quat.v);
	float dot = this->v.dot(_quat.v);

	float scalar = this->w * _quat.w - dot;
	Vec3f vector = _quat.v * this->w + this->v * _quat.w + cross;

	return Quaternion(scalar, vector);
}

Quaternion Quaternion::operator*(const Vec3f& _v) const {

	return *this * Quaternion(0, _v);
}
