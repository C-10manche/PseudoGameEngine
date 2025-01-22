#include "Terrain.h"
#include "../Utils/MyMath.h"
#include <vector>
#include <iostream>

void Terrain::update(float delta_time)
{
	int width = 600;
	int height = 600;

	std::vector<Vertex> vertices;


	for (int y = 0; y < (height - 1); y++) {
		for (int x = 0; x < width; x++) {
			vertices.push_back(Vertex( x, y, 1 ));
			vertices.push_back(Vertex(x, y+1, 1));
		}
	}
}
