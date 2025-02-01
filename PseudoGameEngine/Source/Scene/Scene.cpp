#include "Scene.h"

#include "PhysicsWorld.h"
#include "../GameObject/GameObject.h"
#include "../Components/Camera.h"
#include "../Components/MeshRenderer.h"
#include "../Render/Material.h"
#include "../Render/Shader.h"
#include "../Components/Rigidbody.h"
#include "Mat4f.h"

#include <glfw3.h>  

Scene::Scene() : is_running(false), window(nullptr) {

	physics_handler = new PhysicsHandler();

	main_camera = this->create_camera();

	shaders["default"] = new Shader("Resources/Shaders/default.shader");

	defaultMaterial = new Material("default");
	defaultMaterial->vec3_properties["color"] = { 1.0f, 0.0f, 1.0f };
}

Scene::~Scene() {
	for (GameObject* game_object : game_objects) {
		delete game_object;
	}

	for (std::pair<std::string, Shader*> shader : shaders) {
		delete shader.second;
	}

	delete defaultMaterial;

	delete physics_handler;
}

void Scene::ready()
{

	for (GameObject* game_object : game_objects) {
		game_object->ready();
	}

	// link rigidbodies to physics world bodies
	for (GameObject* game_object : game_objects) {
		if (Rigidbody* body = game_object->get_component<Rigidbody>()) {
			this->physics_handler->add_rigidbody(body);
		}
	}

	this->physics_handler->sync_rigidbody_to_transform();

	this->is_running = true;
}

void Scene::init() { }

void Scene::update(float delta_time) {

	// LOGIC
	for (GameObject* go : game_objects) {
		go->update(delta_time);
	}

	// PHYSICS
	this->physics_handler->step(delta_time);

	// RENDER
	int windows_width, windows_height;
	glfwGetFramebufferSize(window, &windows_width, &windows_height);

	Mat4f view_matrix = main_camera->get_view_matrix();
	Mat4f perspective_matrix = main_camera->get_perspective_matrix((float)windows_width / (float)windows_height);

	glClearColor(0.2f, 0.32f, 0.48f, 1.0f);
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
			/*transform->rotation = Quaternion(Vec3f::UP(), (float)glfwGetTime() * 60);*/
			Mat4f mvp = perspective_matrix * view_matrix * transform->get_model_matrix();
			shader->set_mat4("mvp", mvp.m);

			// for wireframe, temporary because not good
			std::array<float, 3 > wireframe_color{ 0.0f, 1.0f, 0.0f };
			shader->set_vec3("color", &wireframe_color[0]);
			mesh_renderer->draw_wireframe();

			for (std::pair<const std::string, std::array<float, 3>>&prop : material->vec3_properties)
			{
				shader->set_vec3(prop.first, &prop.second[0]);
			}

			mesh_renderer->draw();

		}
	}
}

void Scene::add_game_object(GameObject* game_object)
{
		game_objects.push_back(game_object);
}

void Scene::set_window(GLFWwindow* window) {
	this->window = window;
}

GameObject* Scene::create_sphere(const std::string& name) {
	GameObject* sphere = new GameObject();
	sphere->name = name;
	MeshRenderer* sphere_mesh = sphere->add_component<MeshRenderer>();
	sphere_mesh->mesh = Mesh::generate_uv_sphere_mesh(16, 16);
	sphere_mesh->material = new Material("default");
	sphere_mesh->material->vec3_properties["color"] = { 1.0f, 1.0f, 1.0f };
	sphere_mesh->set_up();
	this->add_game_object(sphere);

	return sphere;
}


GameObject* Scene::create_cube(const std::string& name) {
	GameObject* cube = new GameObject();
	cube->name = name;
	MeshRenderer* cube_mesh = cube->add_component<MeshRenderer>();
	cube_mesh->mesh = Mesh::generate_cube_mesh();
	cube_mesh->material = new Material("default");
	cube_mesh->material->vec3_properties["color"] = { 1.0f, 1.0f, 1.0f };
	cube_mesh->set_up();
	this->add_game_object(cube);

	return cube;
}


GameObject* Scene::create_capsule(const std::string& name) {
	GameObject* capsule = new GameObject();
	capsule->name = name;
	MeshRenderer* capsule_mesh = capsule->add_component<MeshRenderer>();
	capsule_mesh->mesh = Mesh::generate_capsule_mesh(16, 8);
	capsule_mesh->material = new Material("default");
	capsule_mesh->material->vec3_properties["color"] = { 1.0f, 1.0f, 1.0f };
	capsule_mesh->set_up();
	this->add_game_object(capsule);

	return capsule;
}

Camera* Scene::create_camera() {

	GameObject* camera = new GameObject();
	camera->name = "Main Camera";
	this->main_camera = camera->add_component<Camera>();

	this->add_game_object(camera);

	return main_camera;
}
