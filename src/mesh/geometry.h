#pragma once

#include "vertex.h"

#include <vector>

namespace glab::mesh {

struct Geometry {
    std::vector<Vertex> vertices;
    std::vector<std::uint32_t> indices;
};

}  // namespace glab::mesh
