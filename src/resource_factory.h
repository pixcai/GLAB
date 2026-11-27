#pragma once

#include "mesh/mesh.h"
#include "rendering/material.h"

namespace glab {

struct ResourceFactory {
    static mesh::MeshID CreateCube(float size);
    static rendering::MaterialID CreateMaterial();
};

}  // namespace glab
