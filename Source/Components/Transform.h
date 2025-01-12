#pragma once

#include "component.h" 
#include "../Utils/MyMath.h"	

#include <iostream>	

class Transform : public Component {
public:
	Transform();

	Vec3f position;
	Vec3f rotation;
	Vec3f scale;

	Vec3f right();
	Vec3f up();
	Vec3f forward();
};