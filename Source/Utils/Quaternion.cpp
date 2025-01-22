#include "Quaternion.h"

#include "MyMath.h"

Quaternion Quaternion::conjugated()
{
	Quaternion q = *(this);
	q.v *= -1.0f;
	return q;
}

Quaternion Quaternion::operator*(const Vec3f& _vec3f) const
{
	Quaternion p;
	p.w = 0.0f;
	p.v = v;

	Quaternion q = (*this) * p;

	return q;
}

Quaternion Quaternion::operator*(const Quaternion& _quat) const
{
	Quaternion q;
	q.w = w * _quat.w - v.dot(_quat.v);
	q.v = v * _quat.w + _quat.v * w + v.cross(_quat.v);

	return q;
}

Quaternion::Quaternion(const Vec3f& _axis, float _angle, bool _alrdy_in_rad)
{
	float rad_angle = _alrdy_in_rad ? _angle : deg_to_rad(_angle);

	this->w = cosf(rad_angle / 2);
	this->v *= sinf(rad_angle / 2);
}
