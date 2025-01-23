#include "MyMath.h"
#include "Quaternion.h"
#include <string>

// Constants
const double PI = 3.14159265358979323846;

// Vec3f

Vec3f::Vec3f() : x(0.0f), y(0.0f), z(0.0f) {}
Vec3f::Vec3f(float _f) : x(_f), y(_f), z(_f) {}
Vec3f::Vec3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
Vec3f::Vec3f(const Vec3f& _Vec3f) : x(_Vec3f.x), y(_Vec3f.y), z(_Vec3f.z) {}


float Vec3f::magnitude() const {
	return (float)sqrt(x * x + y * y + z * z);
}

Vec3f Vec3f::cross(const Vec3f& other) const {
	Vec3f result;
	result.x = this->y* other.z - other.y * this->z;
	result.y = this->z* other.x - other.z * this->x;
	result.z = this->x* other.y - other.x * this->y;
	return result;
}

float Vec3f::dot(const Vec3f& _Vec3f) const
{
	return x * _Vec3f.x + y * _Vec3f.y + z * _Vec3f.z;
}

float Vec3f::sqr_magnitude() const {
	return x * x + y * y + z * z;
}

Vec3f Vec3f::normalized() const {
	float magnitude = this->magnitude();
	return magnitude == 0 ? Vec3f() : *this / magnitude;
}

void Vec3f::rotate(const Vec3f& _axis, float _angle, bool _alrdy_in_rad)
{
	Quaternion q(_axis, _angle, _alrdy_in_rad);

	Vec3f result = q.rotate(*this);

	x = result.x;
	y = result.y;
	z = result.z;
}

Vec3f Vec3f::operator-() const
{
	return Vec3f(-(this->x), -(this->y), -(this->z));
}

Vec3f Vec3f::operator+(const Vec3f& _Vec3f) const {
	return Vec3f(this->x + _Vec3f.x, this->y + _Vec3f.y, this->z + _Vec3f.z);
}

Vec3f Vec3f::operator-(const Vec3f& _Vec3f) const {
	return Vec3f(this->x - _Vec3f.x, this->y - _Vec3f.y, this->z - _Vec3f.z);
}

Vec3f Vec3f::operator/(const float f) const {
	return Vec3f(this->x / f, this->y / f, this->z / f);
}

Vec3f Vec3f::operator*(const float f) const {
	return Vec3f(this->x * f, this->y * f, this->z * f);
}

Vec3f& Vec3f::operator=(const Vec3f& _Vec3f) {
	if (this != &_Vec3f)
	{
		this->x = _Vec3f.x;
		this->y = _Vec3f.y;
		this->z = _Vec3f.z;
	}
	return *this;
}
Vec3f& Vec3f::operator*=(const Vec3f& _Vec3f) {
	this->x *= _Vec3f.x;
	this->y *= _Vec3f.y;
	this->z *= _Vec3f.z;
	return *this;
}
Vec3f& Vec3f::operator+=(const Vec3f& _Vec3f) {
	this->x += _Vec3f.x;
	this->y += _Vec3f.y;
	this->z += _Vec3f.z;
	return *this;
}
Vec3f& Vec3f::operator-=(const Vec3f& _Vec3f) {
	this->x -= _Vec3f.x;
	this->y -= _Vec3f.y;
	this->z -= _Vec3f.z;
	return *this;
}

std::string Vec3f::print() const {
	std::string v = "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + ")";
	return v;
}

Vec3f Vec3f::RIGHT() {
	return Vec3f(1.0f, 0.0f, 0.0f);
}
Vec3f Vec3f::LEFT() {
	return Vec3f(-1.0f, 0.0f, 0.0f);
}
Vec3f Vec3f::UP() {
	return Vec3f(0.0f, 1.0f, 0.0f);
}
Vec3f Vec3f::DOWN() {
	return Vec3f(0.0f, -1.0f, 0.0f);
}
Vec3f Vec3f::FORWARD() {
	return Vec3f(0.0f, 0.0f, 1.0f);
}
Vec3f Vec3f::BACKWARD() {
	return Vec3f(0.0f, 0.0f, -1.0f);
}
Vec3f Vec3f::ZERO() {
	return Vec3f(0.0f, 0.0f, 0.0f);
}

// Mat4f

Mat4f::Mat4f() {
	// INITIALIZE TO IDENTITY MATRIX
	for(int i = 0; i < 16; i++) {
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

float deg_to_rad(float deg_angle)
{
	float rad_angle = (deg_angle * (float)PI) / 180.0f;
	return rad_angle;
}
