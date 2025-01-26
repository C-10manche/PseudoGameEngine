#include "../Input/Input.h"
#include "../Utils/MyMath.h"
#include "../Utils/Quaternion.h"	
#include "../GameObject/GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "CameraController.h"

CameraController::CameraController() : speed(0), sensitivity(1), pitch(0), yaw(0) {

}

void CameraController::ready()
{
    this->speed = 3.0f;
    this->sensitivity = 50.0f;
    this->pitch = 0.0f;
    this->yaw = 0.0f;
}

void CameraController::update(float delta_time)
{
    handle_movement(delta_time);
}

void CameraController::handle_movement(float delta_time){
    float current_speed = speed * delta_time;
    Transform* transform = game_object->transform;
    Vec3f forward = transform->get_forward();
    Vec3f right = transform->get_right();
    if(Input::is_pressed('W'))        
        transform->position += forward * current_speed;
    if(Input::is_pressed('S'))
        transform->position -= forward * current_speed;
    if(Input::is_pressed('D'))
    {
        transform->position += right * current_speed;
    }
    if(Input::is_pressed('A'))
    {
        transform->position -= right * current_speed;
    }


    if (Input::is_pressed('E')) {
        yaw += delta_time * sensitivity;
    }
    if (Input::is_pressed('Q')) {
        yaw -= delta_time * sensitivity;
    }

    transform->rotation = Quaternion(Vec3f::UP(), yaw) * Quaternion(Vec3f::RIGHT(), pitch);
}

void CameraController::handle_orientation(float delta_time, Vec3f axis)
{
    float sensitivity = 0.1f;

    //yaw += Input::mouse_x * sensitivity;
    //pitch += Input::mouse_y * sensitivity;
}
