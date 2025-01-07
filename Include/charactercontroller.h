#pragma once  

#include "component.h"	
#include <iostream>

class CharacterController : public Component {
public:

	CharacterController();

	void update(float delta_time) override;
};