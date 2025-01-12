#pragma once

#include "component.h" 
#include "../Utils/MyMath.h"	

#include <iostream>	

class Transform : public Component {
public:
	Transform();
	Transform(Vec3f _position, Vec3f _rotation, Vec3f _scale);

	Vec3f position;
	Vec3f rotation;
	Vec3f scale;
};