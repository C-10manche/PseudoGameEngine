#include "Camera.h"
#include "../Utils/MyMath.h"
#include "../Input/Input.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"

#include <glfw3.h>  

Camera::Camera(){

	this->projection_type = Projection::orthographic;
	this->fov = 90.0f;
}

Mat4f Camera::get_view_matrix() {

    const Mat4f& rotation_matrix = get_rotation_matrix();
    const Mat4f& translation_matrix = get_translation_matrix();
    const Mat4f& view_matrix = translation_matrix;// *rotation_matrix;
    return view_matrix;
}

Mat4f Camera::get_rotation_matrix()
{
    Transform* transform = game_object->transform;
    Vec3f u,v,n;
   
    u = transform->get_right();
    v = transform->get_up();
    n = transform->get_forward();

    Mat4f rotation_mat(
        u.x,  u.y,  u.z,  0.0f,
        v.x,  v.y,  v.z,  0.0f,
        n.x,  n.y,  n.z,  0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    return rotation_mat;
}

Mat4f Camera::get_translation_matrix()
{
    Transform* transform = game_object->transform;

    Mat4f translation_mat(
        1.0f, 0.0f, 0.0f, -transform->position.x,
        0.0f, 1.0f, 0.0f, -transform->position.y,
        0.0f, 0.0f, 1.0f, -transform->position.z,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    return translation_mat;
}

void Camera::update(float delta_time)
{

}
