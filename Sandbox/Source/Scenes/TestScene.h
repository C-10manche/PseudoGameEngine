#pragma once

#include "Scene/Scene.h"
#include "Render/Shader.h"
#include "Render/Material.h"
#include "Components/Camera.h"

#include <unordered_map>

class TestScene : public Scene {
public:

	std::unordered_map<std::string, Shader*> shaders;
	Material* defaultMaterial;
	Camera* camera;

	TestScene();

	~TestScene() override;

	void init() override;
	void update(float delta_time) override;
};

