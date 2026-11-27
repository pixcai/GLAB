#pragma once

#include "mesh/mesh.h"

#include <glm/glm.hpp>

namespace glab::rendering {

struct RenderItem {
    mesh::MeshID mesh_id;
    glm::mat4 world_matrix;
};

}  // namespace glab::rendering
