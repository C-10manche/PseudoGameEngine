#include "BallController.h"
#include "Components/Rigidbody.h"
#include "Physics/SphereCollider.h"
#include "GameObject/GameObject.h"
#include "Input/Input.h"
#include "Components/Transform.h"

BallController::BallController() : rb(nullptr) {
  
}

void BallController::ready() {
	rb = this->game_object->add_component<Rigidbody>();
	rb->collider = new SphereCollider();
	rb->use_gravity =  false;
}

void BallController::update(float delta_time) {

    Vec3f move_direction;
    float current_speed = 5 * delta_time;

    if (Input::is_pressed('W'))
        move_direction += Vec3f::UP();
    if (Input::is_pressed('S'))
        move_direction -= Vec3f::UP();
    if (Input::is_pressed('D'))
        move_direction += Vec3f::RIGHT();
    if (Input::is_pressed('A'))
        move_direction -= Vec3f::RIGHT();

    move_direction = move_direction.normalized();

    rb->position += move_direction * current_speed;
}