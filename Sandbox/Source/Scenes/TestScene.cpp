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
#include "Physics/MeshCollider.h"
#include "../Components/BallController.h"
#include "../Components/PlayerController.h"
 
#include <string>
#include <unordered_map>

TestScene::TestScene() {

}

void TestScene::init() {
  
    GameObject* ground = new GameObject();
    ground->transform->position = { 0.0f, 0.0f, 0.0f };
    Terrain* terrain = ground->add_component<Terrain>();
    terrain->size = 10;
    terrain->resolution = 75;
    Quaternion ground_rotation(Vec3f::FORWARD, 0);
    ground->transform->rotation = ground_rotation;
    this->add_game_object(ground);

    GameObject* camera = this->main_camera->game_object;
    camera->transform->position = { 0.0f, 5.0f, 0.0f };
    camera->add_component<PlayerController>();

    physics_handler->set_gravity_force(9.81f);
}
