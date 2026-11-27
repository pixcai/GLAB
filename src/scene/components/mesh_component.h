#pragma once

#include "mesh/mesh.h"
#include "rendering/material.h"

namespace glab::scene {

struct MeshComponent {
    mesh::MeshID mesh_id;
    rendering::MaterialID material_id;
};

}  // namespace glab::scene
