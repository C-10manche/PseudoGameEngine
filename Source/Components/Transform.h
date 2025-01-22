#pragma once

#include "component.h" 
#include "../Utils/MyMath.h"
#include "../Utils/Quaternion.h"	

#include <iostream>	

class Transform : public Component {
public:
	Transform();

	Vec3f position;
	Quaternion rotation;
	Vec3f scale;
	Vec3f up;
	Vec3f forward;
	Vec3f right;
};