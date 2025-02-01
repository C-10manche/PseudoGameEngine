#include "PlayerController.h"

#include "GameObject/GameObject.h"
#include "Input/Input.h"
#include "Components/Transform.h"
#include "Physics/SphereCollider.h"
#include "Vec3f.h"

PlayerController::PlayerController() : transform(nullptr), rb(nullptr), yaw(0), pitch(0), sensitivity(0.1f) {


}

void PlayerController::ready() {

	transform = this->game_object->transform;
	rb = this->game_object->add_component<Rigidbody>();
	rb->collider = new SphereCollider();
	rb->restitution = 0.0f;
}

void PlayerController::update(float delta_time) {

	handle_rotation();
	handle_movement(delta_time);

}

void PlayerController::handle_rotation() {
	std::array<float, 2> mouse_delta = Input::get_mouse_delta();

	yaw += mouse_delta[0] * sensitivity;
	pitch += mouse_delta[1] * sensitivity;
	pitch = clamp(pitch, -80.0f, 80.0f);

	rb->rotation = Quaternion(Vec3f::UP, yaw) * Quaternion(Vec3f::RIGHT, pitch);
}

void PlayerController::handle_movement(float delta_time) {

    float current_speed = 5.0f;
    Vec3f forward = transform->get_forward();
    forward.y = 0;
    forward = forward.normalized();
    Vec3f right = transform->get_right();

    Vec3f move_direction;

    if (Input::is_pressed('W'))
        move_direction += forward;
    if (Input::is_pressed('S'))
        move_direction -= forward;
    if (Input::is_pressed('D'))
        move_direction += right;
    if (Input::is_pressed('A'))
        move_direction -= right;

    //move_direction = move_direction.normalized();
    float y_velocity = rb->velocity.y;
    rb->velocity = move_direction * current_speed + Vec3f::UP * y_velocity;

	// friction
	float friction = 3.0f;
	//rb->add_force(-rb->velocity.normalized() * friction);
}
