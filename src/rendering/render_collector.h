#pragma once

#include "render_queue.h"

namespace glab {

namespace scene {

class Scene;

}

namespace rendering {

struct RenderCollector {
    void Collect(scene::Scene& scene, RenderQueue& out_queue);
};

}  // namespace rendering

}  // namespace glab
