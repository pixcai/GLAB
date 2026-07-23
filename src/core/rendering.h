#pragma once

#include <glm/glm.hpp>

#include "mesh.h"
#include "resource.h"

GLAB_NAMESPACE_BEGIN()

struct RenderQueue {
    static constexpr int kOpaque = 1000;
    static constexpr int kTransparent = 3000;
};

struct RenderItem {
    int render_queue{RenderQueue::kOpaque};
    glm::mat4 world_matrix{1.0f};
    ResourceHandle<Mesh> mesh_handle;
};

struct DrawCommand {
    int render_queue{RenderQueue::kOpaque};
    glm::mat4 world_matrix{1.0f};
    ResourceHandle<Mesh> mesh_handle;
};

GLAB_NAMESPACE_END()
