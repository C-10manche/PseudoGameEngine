#pragma once

#include "component.h" 
#include "mymath.h"	

#include <iostream>	

class Transform : public Component {
public:
	Transform();

	Vec3f position;
	Vec3f rotation;
	Vec3f scale;
};