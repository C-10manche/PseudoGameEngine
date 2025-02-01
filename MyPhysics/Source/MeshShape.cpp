#include "MeshShape.h"
#include "Quaternion.h"

#include <array>
#include <vector>

MeshShape::MeshShape() {

}

std::vector<std::array<float, 3>> MeshShape::get_transformed_vertices(Vec3f position, Quaternion rotation) {
	std::vector<std::array<float, 3>> transformed_vertices;

	for (const std::array<float, 3>& v : vertices) {

		Vec3f vertex_position(v[0], v[1], v[2]);

		vertex_position = rotation.rotate(vertex_position);

		vertex_position + position;
		transformed_vertices.push_back({
			vertex_position.x,
			vertex_position.y,
			vertex_position.z,
			});
	}

	return transformed_vertices;
}