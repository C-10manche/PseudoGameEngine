#include "../Input/Input.h"
#include "../Utils/MyMath.h"
#include "../Utils/Quaternion.h"	
#include "../GameObject/GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "CameraController.h"
#include <array>

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

    if (Input::is_pressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(Input::window, true);

    if(Input::is_pressed('W'))        
        transform->position += forward * current_speed;
    if(Input::is_pressed('S'))
        transform->position -= forward * current_speed;
    if(Input::is_pressed('D'))
        transform->position += right * current_speed;
    if(Input::is_pressed('A'))
        transform->position -= right * current_speed;
}

void CameraController::handle_orientation(float delta_time)
{
    Transform* transform = game_object->transform;

    std::array<float, 2> mouse_delta = Input::get_mouse_delta();


    yaw += mouse_delta[0] * sensitivity;
    pitch += mouse_delta[1] * sensitivity;
    std::cout << yaw << std::endl;

    transform->rotation = Quaternion(Vec3f::UP(), yaw) * Quaternion(Vec3f::RIGHT(), pitch);
}
