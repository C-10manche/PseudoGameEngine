#pragma once

#include "component.h" 
#include "MathHelper.h"
#include "Vec3f.h"
#include "Quaternion.h"	

#include <iostream>	

class Transform : public Component {
public:
	Transform();

	Vec3f position;
	Quaternion rotation;
	Vec3f scale;

	Vec3f get_right();
	Vec3f get_up();
	Vec3f get_forward();

	Mat4f get_model_matrix();
};