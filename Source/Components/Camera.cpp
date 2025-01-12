#include "Camera.h"
#include "../Utils/MyMath.h"
#include "../Input/Input.h"
#include "../GameObject/GameObject.h"

#include <glfw3.h>  

Camera::Camera(){

	this->projection_type = Projection::orthographic;
	this->fov = 90.0f;
}

Mat4f Camera::get_view_matrix() {

    Transform* transform = this->game_object->transform;

    Mat4f translation_mat(
        1.0f, 0.0f, 0.0f, -transform->position.x,
        0.0f, 1.0f, 0.0f, -transform->position.y,
        0.0f, 0.0f, 1.0f, -transform->position.z,
        0.0f, 0.0f, 0.0f, 1.0f);

    Mat4f rotation_mat(
        1.0f, 0.0f, 0.0f, -transform->position.x,
        0.0f, 1.0f, 0.0f, -transform->position.y,
        0.0f, 0.0f, 1.0f, -transform->position.z,
        60.0f, 0.0f, 0.0f, 1.0f);

    return rotation_mat * translation_mat;
}


//void Camera::handle_input(float delta_time){
//    float current_speed = speed * delta_time;
//
//    if(Input::is_pressed('W'))
//        transform.position += forward * current_speed;
//    if(Input::is_pressed('S'))
//        transform.position -= forward * current_speed;
//    if(Input::is_pressed('D'))
//    {
//        Vec3f right = (up.cross(forward));
//        right = right.normalize();
//        right *= current_speed;
//        transform.position += right;
//    }
//    if(Input::is_pressed('A'))
//    {
//        Vec3f left = (forward.cross(up));
//        left = left.normalize();
//        left *= current_speed;
//        transform.position += left;
//    }
//}

void Camera::update(float delta_time)
{

}
