#include "Transform.h"
#include "../Utils/MyMath.h"
#include <cmath>

Transform::Transform() :	position(Vec3f()), 
							rotation(Vec3f()), 
							scale(Vec3f()) 
{

}

Vec3f Transform::right() {
	return Vec3f();
}

Vec3f Transform::up() {
	return Vec3f();
}

Vec3f Transform::forward() {
	return Vec3f();
}
