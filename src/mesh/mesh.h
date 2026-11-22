#pragma once

#include "core/id.h"
#include "vertex.h"

#include <vector>

namespace glab::mesh {

struct Mesh;

using MeshID = core::ID<Mesh>;

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<std::uint32_t> indices;
};

}  // namespace glab::mesh
