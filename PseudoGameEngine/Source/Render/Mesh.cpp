#include "Mesh.h"
#include "MathHelper.h"
#include <cmath>
#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) { 

	this->vertices = vertices;
	this->indices = indices;
}

Mesh* Mesh::generate_cube_mesh() {

    std::vector<Vertex> vertices = {
        {-0.5f,  0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        {-0.5f, -0.5f,  0.5f},

        {-0.5f,  0.5f,  -0.5f},
        { 0.5f,  0.5f,  -0.5f},
        { 0.5f, -0.5f,  -0.5f},
        {-0.5f, -0.5f,  -0.5f}
    };

    std::vector<unsigned int> indices = {
        //FRONT
        0,1,2,
        0,2,3,

        //BACK
        4,7,6,
        6,5,4,

        //TOP  
        0,4,5,
        0,5,1,

        //BOTTOM
        3,6,7,
        3,2,6,

        //RIGHT
        1,5,6,
        1,6,2,

        //LEFT
        4,0,3,
        4,3,7,
    };

	return new Mesh(vertices, indices);
}

Mesh* Mesh::generate_plane_mesh(int x_size, int z_size)
{
    float half_size_x = (float)x_size / 2;
    float half_size_z = (float)z_size / 2;

    std::vector<Vertex> vertices;
    for (int z = 0; z <= z_size; z++) {
        for (int x = 0; x <= x_size; x++) {
            Vertex new_vertex{ (float)x - half_size_x, 0.0f, (float)z - half_size_z};
            vertices.push_back(new_vertex);
        }
    }

    int vert = 0;

    std::vector<unsigned int> indices;
    for (int z = 0; z < z_size; z++) {
        for (int x = 0; x < x_size; x++) {

            indices.push_back(vert);
            indices.push_back(vert + x_size + 1);
            indices.push_back(vert + x_size + 2);

            indices.push_back(vert);
            indices.push_back(vert + x_size + 2);
            indices.push_back(vert + 1);

            vert++;
        }
        vert++;
    }
    return new Mesh(vertices, indices);
}

Mesh* Mesh::generate_uv_sphere_mesh(int segments, int rings) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= rings; i++) {
        float phi = (float)i / rings * (float)PI;
        for (int j = 0; j <= segments; j++) {
            float theta = (float)j / segments * 2 * (float)PI;

            float x = std::cosf(theta) * std::sinf(phi) * 0.5f;
            float y = std::cosf(phi) * 0.5f;
            float z = std::sinf(theta) * std::sinf(phi) * 0.5f;
            Vertex vertex({ x, y , z });

            vertices.push_back(vertex);
        }
    }

    for (int i = 0; i < rings; i++) {
        for (int j = 0; j < segments; j++) {

            int vertex_index = j + (segments + 1) * i;

            indices.push_back(vertex_index);
            indices.push_back(vertex_index + segments + 1);
            indices.push_back(vertex_index + 1);

            indices.push_back(vertex_index + segments + 1);
            indices.push_back(vertex_index + segments + 2);
            indices.push_back(vertex_index + 1);
        }
    }

    return new Mesh(vertices, indices);
}


Mesh* Mesh::generate_capsule_mesh(int segments, int rings_per_hemisphere) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // top hemisphere
    for (int i = 0; i <= rings_per_hemisphere; i++) {
        float phi = (float)i / rings_per_hemisphere * (float)PI / 2;
        for (int j = 0; j <= segments; j++) {
            float theta = (float)j / segments * 2 * (float)PI;

            float x = std::cosf(theta) * std::sinf(phi) * 0.5f;
            float y = 0.5f + std::cosf(phi) * 0.5f;
            float z = std::sinf(theta) * std::sinf(phi) * 0.5f;
            Vertex vertex({ x, y , z });

            vertices.push_back(vertex);
        }
    }

    // bottom hemisphere
    for (int i = 0; i <= rings_per_hemisphere; i++) {
        float phi = (float)PI / 2 + (float)i / rings_per_hemisphere * (float)PI / 2;
        for (int j = 0; j <= segments; j++) {
            float theta = (float)j / segments * 2 * (float)PI;

            float x = std::cosf(theta) * std::sinf(phi) * 0.5f;
            float y = -0.5f + std::cosf(phi) * 0.5f;
            float z = std::sinf(theta) * std::sinf(phi) * 0.5f;
            Vertex vertex({ x, y , z });

            vertices.push_back(vertex);
        }
    }

    // indices
    for (int i = 0; i < rings_per_hemisphere * 2 + 1; i++) {
        for (int j = 0; j < segments; j++) {

            int vertex_index = j + (segments + 1) * i;

            indices.push_back(vertex_index);
            indices.push_back(vertex_index + segments + 1);
            indices.push_back(vertex_index + 1);

            indices.push_back(vertex_index + segments + 1);
            indices.push_back(vertex_index + segments + 2);
            indices.push_back(vertex_index + 1);
        }
    }

    return new Mesh(vertices, indices);
}