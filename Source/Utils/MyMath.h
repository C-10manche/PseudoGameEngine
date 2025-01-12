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

	Vec3f cross(Vec3f other) const;

	float sqr_magnitude() const;

	Vec3f normalize() const;

	Vec3f operator+(const Vec3f& _Vec3f) const;

	Vec3f operator-(const Vec3f& _Vec3f) const;

	Vec3f operator/(const float f) const;

	Vec3f operator*(const float f) const;
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
																					 
class Mat4f {
public:
	float m[16];

	Mat4f();

	Mat4f(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	Mat4f operator*(const Mat4f& rhs) const;
	Mat4f operator+(const Mat4f& rhs) const;

	std::string to_string() const;
};