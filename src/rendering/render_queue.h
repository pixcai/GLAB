#pragma once

#include "render_item.h"

#include <vector>

namespace glab::rendering {

struct RenderQueue {
    std::vector<RenderItem> items;
};

}  // namespace glab::rendering
