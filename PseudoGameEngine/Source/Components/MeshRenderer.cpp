#include <iostream>
#include "MeshRenderer.h"
#include "../Render/Shader.h"
#include "../Render/Mesh.h"

#include "glad/glad.h"

MeshRenderer::MeshRenderer() : VAO(), VBO(), EBO() {

	mesh = nullptr;
	material = nullptr;
}

MeshRenderer::~MeshRenderer() { 

	delete mesh;
}

void MeshRenderer::set_up() {


	if (this->mesh == nullptr) {
		std::cout << "ERROR::MESHRENDERER\n" << "CANNOT SET UP WITHOUT A MESH ASSIGNED";
		return;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->mesh->vertices.size() * sizeof(Vertex), &this->mesh->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mesh->indices.size() * sizeof(unsigned int), &this->mesh->indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

void MeshRenderer::draw() {
	if (this->mesh == nullptr) {
		std::cout << "ERROR::MESHRENDERER\n" << "CANNOT DRAW WITHOUT A MESH ASSIGNED";
		return;
	}

	glBindVertexArray(VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, (GLsizei)this->mesh->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
