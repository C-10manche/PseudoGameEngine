#include "Mesh.h"

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

    std::vector<Vertex> vertices;
    for (int z = 0; z <= z_size; z++) {
        for (int x = 0; x <= x_size; x++) {
            Vertex new_vertex{ x, 0.0f, z };
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
