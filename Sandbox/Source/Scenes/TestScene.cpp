#include "TestScene.h"

#include "GameObject/GameObject.h"
#include "Components/MeshRenderer.h"	
#include "MathHelper.h"	
#include "Vec3f.h"
#include "Quaternion.h"
#include "Render/Material.h"
#include "Components/Transform.h"
#include "Render/Mesh.h"
#include "Components/Camera.h"
#include "Components/CameraController.h"
#include "Components/Terrain.h"
#include "Components/Rigidbody.h"
#include "Physics/SphereCollider.h"
#include "../Components/BallController.h"
 
#include <string>
#include <unordered_map>

TestScene::TestScene() {

}


void TestScene::init() {

    GameObject* sphere = this->create_sphere();
    sphere->transform->position = { 0.0f, 0.5f, 5.0f };
    Rigidbody* rb = sphere->add_component<Rigidbody>();
    rb->collider = new SphereCollider();
    rb->is_static = true;



    GameObject* ball = this->create_sphere();
    ball->transform->position = { 0.0f, 5.0f, 5.0f };
    ball->add_component<BallController>();

    GameObject* ground = new GameObject();
    ground->transform->position = { 0.0f, 0.0f, 0.0f };
    Terrain* terrain = ground->add_component<Terrain>();
    terrain->size = 100;
    terrain->resolution = 100;
    this->add_game_object(ground);

    GameObject* camera = this->main_camera->game_object;
    camera->transform->position = { 0.0f, 1.5f, 0.0f };
    camera->add_component<CameraController>();

    physics_handler->set_gravity_force(9.81f);
}
