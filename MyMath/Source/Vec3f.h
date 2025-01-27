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

	Vec3f operator+(const Vec3f& _Vec3f) const;
	Vec3f operator-(const Vec3f& _Vec3f) const;
	Vec3f& operator=(const Vec3f& _Vec3f);
	Vec3f& operator*=(const Vec3f& _Vec3f);
	Vec3f& operator+=(const Vec3f& _Vec3f);
	Vec3f& operator-=(const Vec3f& _Vec3f);

	std::string print() const;

	static Vec3f RIGHT();
	static Vec3f LEFT();
	static Vec3f UP();
	static Vec3f DOWN();
	static Vec3f FORWARD();
	static Vec3f BACKWARD();
	static Vec3f ZERO();
};
