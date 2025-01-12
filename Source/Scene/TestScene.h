#pragma once

#include "Scene.h"
#include "../Render/Shader.h"
#include "../Render/Material.h"
#include <unordered_map>

class TestScene : public Scene {
public:

	std::unordered_map<std::string, Shader*> shaders;
	Material* defaultMaterial;

	TestScene(GLFWwindow* _window);

	~TestScene() override;

	void init() override;
	void update(float delta_time) override;
};

