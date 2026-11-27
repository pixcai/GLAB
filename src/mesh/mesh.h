#pragma once

#include "core/id.h"
#include "rendering/buffer_object.h"
#include "rendering/vertex_layout.h"
#include "vertex.h"

#include <vector>

namespace glab::mesh {

struct Mesh;

using MeshID = core::ID<Mesh>;

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<std::uint32_t> indices;
    rendering::VertexLayoutType layout_type{rendering::VertexLayoutType::kDefault};
    rendering::BufferBlock* block{nullptr};
    bool is_dirty{true};
};

}  // namespace glab::mesh
