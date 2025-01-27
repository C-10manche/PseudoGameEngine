#include "Mat4f.h"

Mat4f::Mat4f() {
	// INITIALIZE TO IDENTITY MATRIX
	for (int i = 0; i < 16; i++) {
		m[i] = i % 5 == 0 ? 1.0f : 0.0f;
	}
}

Mat4f::Mat4f(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) {

	m[0] = m00; m[1] = m01; m[2] = m02; m[3] = m03;
	m[4] = m10; m[5] = m11; m[6] = m12; m[7] = m13;
	m[8] = m20; m[9] = m21; m[10] = m22; m[11] = m23;
	m[12] = m30; m[13] = m31; m[14] = m32; m[15] = m33;
}

Mat4f Mat4f::operator*(const Mat4f& rhs) const {
	Mat4f result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
				sum += this->m[i * 4 + k] * rhs.m[k * 4 + j];
			}
			result.m[i * 4 + j] = sum;
		}
	}

	return result;
}

Mat4f Mat4f::operator+(const Mat4f& rhs) const {
	Mat4f result;

	for (int i = 0; i < 16; i++) {
		result.m[i] = this->m[i] + rhs.m[i];
	}

	return result;
}

std::string Mat4f::to_string() const {
	std::string matrix_string;

	for (int i = 0; i < 16; i++) {
		matrix_string += std::to_string(this->m[i]) + (i % 4 == 3 ? '\n' : ' ');
	}

	return matrix_string;
}