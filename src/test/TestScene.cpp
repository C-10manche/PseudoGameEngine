#include "TestScene.h"
#include "core/GameObject.h"
#include "core/CharacterController.h"

void TestScene::init() {

	GameObject* game_object = new GameObject();
	game_object->name = "Player";
	game_object->add_component<CharacterController>();

	this->add_game_object(game_object);
}

void TestScene::update(float delta_time) {
	for (GameObject* go : game_objects) {
		go->update(delta_time);
	}
}