#include "Mesh.h"
#include "MathHelper.h"
#include "FastNoiseLite.h"
#include <cmath>
#include <iostream>
#include <random>

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

Mesh* Mesh::generate_plane_mesh(float size, int resolution)
{
    float half_res = (float)resolution / 2;

    //setup le noise
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

    //setup random avec Mersenne Twister pour le seed
    std::mt19937 mt;
    noise.SetSeed(mt());

    noise.SetFrequency(0.01f);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(5);
    noise.SetFractalLacunarity(2.0f);
    noise.SetFractalGain(0.5f);


    std::vector<Vertex> vertices;
    float x_pos, y_pos, z_pos;
    int v = 0;
    for (int z = 0; z <= resolution; z++) {
        for (int x = 0; x <= resolution; x++) {
            x_pos = (x - half_res)* size / resolution;
            z_pos = (z - half_res) * size / resolution;
            y_pos = noise.GetNoise((float)x, (float)z);
            Vertex new_vertex{ x_pos, y_pos, z_pos };
            vertices.push_back(new_vertex);
        }
    }

    int vert = 0;
    std::vector<unsigned int> indices;
    for (int z = 0; z < resolution; z++) {
        for (int x = 0; x < resolution; x++) {

            indices.push_back(vert);
            indices.push_back(vert + resolution + 1);
            indices.push_back(vert + resolution + 2);

            indices.push_back(vert);
            indices.push_back(vert + resolution + 2);
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
            indices.push_back(vertex_index + 1);
            indices.push_back(vertex_index + segments + 1);

            indices.push_back(vertex_index + segments + 1);
            indices.push_back(vertex_index + 1);
            indices.push_back(vertex_index + segments + 2);
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
            indices.push_back(vertex_index + 1);
            indices.push_back(vertex_index + segments + 1);

            indices.push_back(vertex_index + segments + 1);
            indices.push_back(vertex_index + 1);
            indices.push_back(vertex_index + segments + 2);
        }
    }

    return new Mesh(vertices, indices);
}