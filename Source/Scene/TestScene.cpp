#include "TestScene.h"
#include "../GameObject/GameObject.h"
#include "../Components/CharacterController.h"
#include "../Render/Shader.h"
#include "../Components/MeshRenderer.h"	
#include "../Utils/MyMath.h"	
#include "../Render/Material.h"
#include "../Components/Transform.h"
#include "../Render/Mesh.h"
#include "../Render/Material.h"

#include <glfw3.h>  
#include <string>
#include <unordered_map>

TestScene::TestScene(GLFWwindow* _window) :	Scene(_window) {

    shaders["default"] = new Shader("Resources/Shaders/default.shader");

    defaultMaterial = new Material("default");
    defaultMaterial->vec3_properties["color"] = { 1.0f, 0.0f, 1.0f };
}

TestScene::~TestScene() {
    for (std::pair<std::string, Shader*> shader : shaders) {
        delete shader.second;
    }

    delete defaultMaterial;
}

void TestScene::init() {

	GameObject* cube1 = new GameObject();
    cube1->name = "Cube 1";
    cube1->transform->position = { 1.0, 1.0f, 3.0f };
    MeshRenderer* cube1_mesh = cube1->add_component<MeshRenderer>();
    cube1_mesh->mesh = Mesh::generate_cube_mesh();
    //cube1_mesh->material = new Material("default");
    //cube1_mesh->material->vec3_properties["color"] = { 1.0f, 0.0f, 0.0f };
    cube1_mesh->set_up();
	this->add_game_object(cube1);


    GameObject* cube2 = new GameObject();
    cube2->name = "Cube 2";
    cube2->transform->position = { -1.0, 0.0f, 3.0f };
    MeshRenderer* cube2_mesh = cube2->add_component<MeshRenderer>();
    cube2_mesh->mesh = Mesh::generate_cube_mesh();
    cube2_mesh->material = new Material("default");
    cube2_mesh->material->vec3_properties["color"] = { 0.0f, 1.0f, 0.0f };
    cube2_mesh->set_up();
    this->add_game_object(cube2);
}

void TestScene::update(float delta_time) {

	for (GameObject* go : game_objects) {
		go->update(delta_time);
	}

    int windows_width, windows_height;
    glfwGetFramebufferSize(window, &windows_width, &windows_height);

    Mat4f scale(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    float angle = (float)glfwGetTime() * 60;
    float angle_rad = angle * (float)PI / 180.0f;
    Mat4f rotation(
        std::cos(angle_rad), 0.0f, -std::sin(angle_rad), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        std::sin(angle_rad), 0.0f, std::cos(angle_rad), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    Mat4f translation(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    Mat4f model = translation * rotation * scale;

    float l = -1, r = 1;
    float t = -1, b = 1;

    float deg_fov = 90.0f;

    float rad_fov = ((deg_fov * 0.5f) * (float)PI) / 180.0f;
    float tan_fov = std::tanf(rad_fov);
    float d = 1.0f / tan_fov;

    // aspect ratio
    float ar = (float)windows_width / (float)windows_height;


    float near_z = 1.0f;
    float far_z = 10.0f;

    float range_z = near_z - far_z;

    float a_z = (-far_z - near_z) / range_z;
    float b_z = 2.0f * far_z * near_z / range_z;

    Mat4f perspective(
        d / ar, 0.0f, 0.0f, 0.0f,
        0.0f, d, 0.0f, 0.0f,
        0.0f, 0.0f, a_z, b_z,
        0.0f, 0.0f, 1.0f, 0.0f
    );

    Mat4f orthographic(
        2.0f / (r - l), 0.0f, 0.0f, -(r + l) / (r - l),
        0.0f, 2.0f / (t - b), 0.0f, -(t + b) / (t - b),
        0.0f, 0.0f, 2.0f / (far_z - near_z), -(far_z + near_z) / (far_z - near_z),
        0.0f, 0.0f, 0.0f, 1.0f
    );

    Mat4f mvp = perspective * model;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (GameObject* go : game_objects) {
		if (MeshRenderer* mesh_renderer = go->get_component<MeshRenderer>()) {
            
            Material* material = mesh_renderer->material;

            if (material == nullptr) {
                material = defaultMaterial;
            }

            Shader* shader = this->shaders.find(material->shader_name)->second;

            if (shader == nullptr) {

                std::cout << "ERROR::UPDATE\n" << "This shader \"" << material->shader_name << "\"" << "does not exist";
                return;
            }

            shader->use();

            Transform* transform = go->transform;

            Mat4f t = Mat4f(
                1.0f, 0.0f, 0.0f, transform->position.x,
                0.0f, 1.0f, 0.0f, transform->position.y,
                0.0f, 0.0f, 1.0f, transform->position.z,
                0.0f, 0.0f, 0.0f, 1.0f);
            
            Mat4f m = perspective * t * rotation;

            shader->set_mat4("mvp", m.m);
            for (std::pair<const std::string, std::array<float, 3>>& prop : material->vec3_properties)
            {
                shader->set_vec3(prop.first, &prop.second[0]);
            }

            mesh_renderer->draw();
		}
	}
}
