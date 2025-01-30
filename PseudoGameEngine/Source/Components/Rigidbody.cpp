#include "Rigidbody.h"

Rigidbody::Rigidbody() :	position(0), 
							velocity(0), 
							acceleration(0), 
							use_gravity(true),
							is_static(false),
							collider(nullptr)
{

}

Rigidbody::	~Rigidbody() {

	delete collider;
}
