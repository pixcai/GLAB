#pragma once

#include "render_item.h"
#include "rendering/material.h"

#include <vector>

namespace glab::rendering {

struct RenderTask {
    MaterialID material_id;
    std::vector<RenderItem> items;
};

struct RenderQueue {
    std::vector<RenderTask> opaque;
    std::vector<RenderTask> transparent;
};

}  // namespace glab::rendering
