#include "Terrain.h"
#include "../GameObject/GameObject.h"
#include "../Components/MeshRenderer.h"	

#include <vector>
#include <iostream>

Terrain::Terrain() : size(1), resolution(1) {

}

void Terrain::ready() {
    MeshRenderer* plane_mesh = game_object->add_component<MeshRenderer>();
    plane_mesh->mesh = Mesh::generate_plane_mesh(size, resolution);
    plane_mesh->material = new Material("default");
    plane_mesh->material->vec3_properties["color"] = { 0.15f, 0.15f, 0.15f };
    plane_mesh->set_up();
}

void Terrain::update(float delta_time)
{
}
