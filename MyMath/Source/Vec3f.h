#pragma once

#include <string>

extern const double PI;

class Vec3f {
public:
	float x, y, z;

	Vec3f();
	Vec3f(float _f);
	Vec3f(float _x, float _y, float _z);
	Vec3f(const Vec3f& _Vec3f);


	float magnitude() const;

	Vec3f cross(const Vec3f& other) const;

	float dot(const Vec3f& _Vec3f) const;

	float sqr_magnitude() const;

	Vec3f normalized() const;

	void rotate(const Vec3f& _axis, float _angle, bool _alrdy_in_rad = false);

	Vec3f operator-() const;

	Vec3f operator/(float f) const;
	Vec3f operator*(float f) const;
	friend Vec3f operator*(float f, Vec3f vector);
	Vec3f operator+(const Vec3f& _Vec3f) const;
	Vec3f operator-(const Vec3f& _Vec3f) const;
	Vec3f& operator=(const Vec3f& _Vec3f);
	Vec3f& operator*=(const Vec3f& _Vec3f);
	Vec3f& operator+=(const Vec3f& _Vec3f);
	Vec3f& operator-=(const Vec3f& _Vec3f);

	std::string print() const;

	static const Vec3f RIGHT;
	static const Vec3f LEFT;
	static const Vec3f UP;
	static const Vec3f DOWN;
	static const Vec3f FORWARD;
	static const Vec3f BACKWARD;
	static const Vec3f ZERO;
};
