#pragma once

#include "mesh/mesh.h"

namespace glab {

struct ResourceFactory {
    static mesh::MeshID CreateCube(float size);
};

}  // namespace glab
