#include "TestScene.h"
#include "../GameObject/GameObject.h"
#include "../Components/CharacterController.h"
#include "../Render/Shader.h"
#include "../Components/MeshRenderer.h"	
#include "../Utils/MyMath.h"	
#include "../Render/Material.h"
#include "../Components/Transform.h"
#include "../Render/Mesh.h"
#include "../Components/Camera.h"
#include "../Components/CameraController.h"
#include "../Components/Terrain.h"

#include <glfw3.h>  
#include <string>
#include <unordered_map>

TestScene::TestScene(GLFWwindow* _window) :	Scene(_window) {
    camera = NULL;
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
    cube1_mesh->material = new Material("default");
    cube1_mesh->material->vec3_properties["color"] = { 1.0f, 0.0f, 0.0f };
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

    GameObject* main_camera = new GameObject();
    main_camera->transform->position = { 0.0f, 0.0f, 0.0f };
    main_camera->name = "Main Camera";
    camera = main_camera->add_component<Camera>();
    main_camera->add_component<CameraController>();
    this->add_game_object(main_camera);

    GameObject* ground = new GameObject();
    ground->transform->position = { 0.0f, -1.0f, 0.0f };
    ground->name = "Ground";
    Terrain* terrain = ground->add_component<Terrain>();
    terrain->width = 4;
    terrain->height = 4;
    
    this->add_game_object(ground);

}

void TestScene::update(float delta_time) {

	for (GameObject* go : game_objects) {
		go->update(delta_time);
	}

    int windows_width, windows_height;
    glfwGetFramebufferSize(window, &windows_width, &windows_height);

    //some old code
    {
        //Mat4f scale(
        //    1.0f, 0.0f, 0.0f, 0.0f,
        //    0.0f, 1.0f, 0.0f, 0.0f,
        //    0.0f, 0.0f, 1.0f, 0.0f,
        //    0.0f, 0.0f, 0.0f, 1.0f);

        //float angle = (float)glfwGetTime() * 60;
        //float angle_rad = angle * (float)PI / 180.0f;
        //Mat4f rotation(
        //    std::cos(angle_rad), 0.0f, -std::sin(angle_rad), 0.0f,
        //    0.0f, 1.0f, 0.0f, 0.0f,
        //    std::sin(angle_rad), 0.0f, std::cos(angle_rad), 0.0f,
        //    0.0f, 0.0f, 0.0f, 1.0f);

        //Mat4f translation(
        //    1.0f, 0.0f, 0.0f, 0.0f,
        //    0.0f, 1.0f, 0.0f, 0.0f,
        //    0.0f, 0.0f, 1.0f, 3.0f,
        //    0.0f, 0.0f, 0.0f, 1.0f);

        //Mat4f model = translation * rotation * scale;
    }

    float deg_fov = 90.0f;
    float rad_fov = ((deg_fov * 0.5f) * (float)PI) / 180.0f;
    float tan_fov = std::tanf(rad_fov);
    float d = 1.0f / tan_fov;

    // aspect ratio
    float ar = (float)windows_width / (float)windows_height;

    float near_z = 0.01f;
    float far_z = 10.0f;
    float range_z = near_z - far_z;

    float a_z = (-far_z - near_z) / range_z;
    float b_z = 2.0f * far_z * near_z / range_z;

    Mat4f perspective(
        d / ar, 0.0f, 0.0f, 0.0f,
        0.0f, d, 0.0f, 0.0f,
        0.0f, 0.0f, a_z, b_z,
        0.0f, 0.0f, 1.0f, 0.0f);

    //float l = -1, r = 1;
    //float t = -1, b = 1;

    //Mat4f orthographic(
    //    2.0f / (r - l), 0.0f, 0.0f, -(r + l) / (r - l),
    //    0.0f, 2.0f / (t - b), 0.0f, -(t + b) / (t - b),
    //    0.0f, 0.0f, 2.0f / (far_z - near_z), -(far_z + near_z) / (far_z - near_z),
    //    0.0f, 0.0f, 0.0f, 1.0f
    //);

    //Mat4f mvp = perspective * model;



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
            Mat4f mvp = perspective * camera->get_view_matrix() * transform->get_model_matrix();

            shader->set_mat4("mvp", mvp.m);
            for (std::pair<const std::string, std::array<float, 3>>& prop : material->vec3_properties)
            {
                shader->set_vec3(prop.first, &prop.second[0]);
            }

            mesh_renderer->draw();
		}
	}
}
