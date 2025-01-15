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

    Transform* transform = game_object->transform;

    Mat4f translation_mat(
        1.0f, 0.0f, 0.0f, -transform->position.x,
        0.0f, 1.0f, 0.0f, -transform->position.y,
        0.0f, 0.0f, 1.0f, -transform->position.z,
        0.0f, 0.0f, 0.0f, 1.0f);

    return translation_mat;
}

void Camera::update(float delta_time)
{

}
