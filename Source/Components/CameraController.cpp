#include "../Input/Input.h"
#include "../Utils/MyMath.h"
#include "../GameObject/GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "CameraController.h"

void CameraController::ready()
{
    speed = 3.0f;
}

void CameraController::update(float delta_time)
{
    handle_movements(delta_time);
}

void CameraController::handle_movements(float delta_time){
    float current_speed = speed * delta_time;
    Transform* transform = game_object->transform;
    Vec3f forward = Vec3f(0, 0, 1);
    Vec3f up = Vec3f(0, 1, 0);
    if(Input::is_pressed('W'))        
        transform->position += forward * current_speed;
    if(Input::is_pressed('S'))
        transform->position -= forward * current_speed;
    if(Input::is_pressed('D'))
    {
        Vec3f right = (up.cross(forward));
        right = right.normalize();
        right *= current_speed;
        transform->position += right;
    }
    if(Input::is_pressed('A'))
    {
        Vec3f left = (forward.cross(up));
        left = left.normalize();
        left *= current_speed;
        transform->position += left;
    }
}