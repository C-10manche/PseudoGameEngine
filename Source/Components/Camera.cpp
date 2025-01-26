#include "Camera.h"
#include "../Utils/MyMath.h"
#include "../Input/Input.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"

#include <glfw3.h>  

Camera::Camera(){

	this->projection_type = Projection::orthographic;
	this->fov = 60.0f;
    this->near = 0.01f;
    this->far = 100.0f;
    this->window = nullptr;
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

Mat4f Camera::get_view_matrix() {

    const Mat4f& rotation_matrix = get_rotation_matrix();
    const Mat4f& translation_matrix = get_translation_matrix();
    //const Mat4f& view_matrix = translation_matrix * rotation_matrix;
    const Mat4f& view_matrix = rotation_matrix * translation_matrix;
    return view_matrix;
}

Mat4f Camera::get_perspective_matrix() {

    float rad_fov = ((this->fov * 0.5f) * (float)PI) / 180.0f;
    float tan_fov = std::tanf(rad_fov);
    float d = 1.0f / tan_fov;

    // aspect ration
    int windows_width, windows_height;
    glfwGetFramebufferSize(window, &windows_width, &windows_height);
    float ar = (float)windows_width / (float)windows_height;

    float near_z = 0.01f;
    float far_z = 100.0f;
    float range_z = near_z - far_z;

    float a_z = (-far_z - near_z) / range_z;
    float b_z = 2.0f * far_z * near_z / range_z;

    return Mat4f(
        d / ar, 0.0f, 0.0f, 0.0f,
        0.0f, d, 0.0f, 0.0f,
        0.0f, 0.0f, a_z, b_z,
        0.0f, 0.0f, 1.0f, 0.0f);
}

void Camera::update(float delta_time)
{

}
