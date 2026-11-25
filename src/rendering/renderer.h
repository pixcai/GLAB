#pragma once

#include "render_item.h"

namespace glab::rendering {

class MeshRenderer {
public:
    void BeginFrame();
    void Render(const RenderItem& item);
    void EndFrame();
};

}  // namespace glab::rendering
