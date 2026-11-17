#pragma once

#include <vector>

namespace glab::rendering {

struct MeshItem {};

struct RenderQueue {
    std::vector<MeshItem> meshes;
};

}  // namespace glab::rendering
