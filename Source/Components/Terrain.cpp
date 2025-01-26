#include "Terrain.h"
#include "../Utils/MyMath.h"
#include "../GameObject/GameObject.h"
#include "../Components/MeshRenderer.h"	

#include <vector>
#include <iostream>

void Terrain::ready() {
    MeshRenderer* plane_mesh = game_object->add_component<MeshRenderer>();
    plane_mesh->mesh = Mesh::generate_plane_mesh((int)width, (int)height);
    plane_mesh->material = new Material("default");
    plane_mesh->material->vec3_properties["color"] = { 0.0f, 0.0f, 1.0f };
    plane_mesh->set_up();
}

void Terrain::update(float delta_time)
{
}
