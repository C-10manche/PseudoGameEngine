#pragma once
#include <vector>
#include "../Components/Component.h"
#include "../Render/Shader.h"
#include "../Render/Material.h"
#include "../Render/Mesh.h"

class MeshRenderer : public Component
{
public:

	unsigned int VAO, VBO, EBO;
	Mesh* mesh;
	Material* material;

	MeshRenderer();
	~MeshRenderer() override;

	void draw();

	void draw_wireframe();

	void set_up();
};

