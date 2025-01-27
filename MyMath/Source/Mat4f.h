#pragma once
#include <string>

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