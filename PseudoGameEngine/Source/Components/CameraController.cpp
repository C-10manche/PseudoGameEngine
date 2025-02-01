#include "../Input/Input.h"
#include "MathHelper.h"
#include "Vec3f.h"	
#include "Quaternion.h"	
#include "../GameObject/GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "CameraController.h"
#include <array>

#include <glfw3.h>

CameraController::CameraController() : speed(0.0f), sensitivity(1.0f), pitch(0.0f), yaw(0.0f) {

}

void CameraController::ready()
{
    this->speed = 3.0f;
    this->sensitivity = 0.1f;
    this->pitch = 0.0f;
    this->yaw = 0.0f;
}

void CameraController::update(float delta_time)
{
    handle_orientation(delta_time);
    handle_movement(delta_time);
}

void CameraController::handle_movement(float delta_time){

    float current_speed = speed * delta_time;
    Transform* transform = game_object->transform;
    Vec3f forward = transform->get_forward();
    forward.y = 0;
    forward = forward.normalized();
    Vec3f right = transform->get_right();

    Vec3f move_direction;

    if(Input::is_pressed('U'))        
        move_direction += forward;
    if(Input::is_pressed('J'))
        move_direction -= forward;
    if(Input::is_pressed('K'))
        move_direction += right;
    if(Input::is_pressed('H'))
        move_direction -= right;

    move_direction = move_direction.normalized();

    transform->position += move_direction * current_speed;
}

void CameraController::handle_orientation(float delta_time)
{
    Transform* transform = game_object->transform;

    std::array<float, 2> mouse_delta = Input::get_mouse_delta();

    yaw += mouse_delta[0] * sensitivity;
    pitch += mouse_delta[1] * sensitivity;

    transform->rotation = Quaternion(Vec3f::UP, yaw) * Quaternion(Vec3f::RIGHT, pitch);
}
