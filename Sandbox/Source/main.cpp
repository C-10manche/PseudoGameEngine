#include <iostream>

#include "Engine.h"
#include "Scenes/TestScene.h"

int main() {

	Engine engine;

	if (!engine.init())
		return -1;

	TestScene* scene = new TestScene();

	engine.load_scene(scene);

	engine.set_max_fps(60);

	engine.run();

	delete scene;

	return 0;
} 