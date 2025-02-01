#include "Vec3f.h"
#include <string>
#include "Quaternion.h"


Vec3f::Vec3f() : x(0.0f), y(0.0f), z(0.0f) {}
Vec3f::Vec3f(float _f) : x(_f), y(_f), z(_f) {}
Vec3f::Vec3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
Vec3f::Vec3f(const Vec3f& _Vec3f) : x(_Vec3f.x), y(_Vec3f.y), z(_Vec3f.z) {}

const Vec3f Vec3f::RIGHT(1.0f, 0.0f, 0.0f);
const Vec3f Vec3f::UP(0.0f, 1.0f, 0.0f);
const Vec3f Vec3f::FORWARD(0.0f, 0.0f, 1.0f);
const Vec3f Vec3f::LEFT(-1.0f, 0.0f, 0.0f);
const Vec3f Vec3f::DOWN(0.0f, -1.0f, 0.0f);
const Vec3f Vec3f::BACKWARD(0.0f, 0.0f, -1.0f);
const Vec3f Vec3f::ZERO(0.0f);


float Vec3f::magnitude() const {
	return (float)sqrt(x * x + y * y + z * z);
}

Vec3f Vec3f::cross(const Vec3f& other) const {
	Vec3f result;
	result.x = this->y * other.z - other.y * this->z;
	result.y = this->z * other.x - other.z * this->x;
	result.z = this->x * other.y - other.x * this->y;

	return result;
}

float Vec3f::dot(const Vec3f& _Vec3f) const {
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

Vec3f operator*(float f, Vec3f vector) {
	return Vec3f(vector.x * f, vector.y * f, vector.z * f);
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
