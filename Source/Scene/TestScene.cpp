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
#include "../Utils/Quaternion.h"

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
    this->camera = main_camera->add_component<Camera>();
    this->camera->window = this->window;
    main_camera->add_component<CameraController>();
    this->add_game_object(main_camera);

}

void TestScene::update(float delta_time) {

	for (GameObject* go : game_objects) {
		go->update(delta_time);
	}

    int windows_width, windows_height;
    glfwGetFramebufferSize(window, &windows_width, &windows_height);


    Mat4f view_matrix = camera->get_view_matrix();
    Mat4f perspective_matrix = camera->get_perspective_matrix();

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
            transform->rotation = Quaternion(Vec3f::UP(), (float)glfwGetTime() * 60);
            Mat4f mvp = perspective_matrix * view_matrix * transform->get_model_matrix();

            shader->set_mat4("mvp", mvp.m);
            for (std::pair<const std::string, std::array<float, 3>>& prop : material->vec3_properties)
            {
                shader->set_vec3(prop.first, &prop.second[0]);
            }

            mesh_renderer->draw();
		}
	}
}
