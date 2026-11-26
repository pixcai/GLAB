#pragma once

namespace glab {

namespace scene {

class Scene;

}

namespace rendering {

struct RenderQueue;

struct Collector {
    void Collect(scene::Scene& scene, RenderQueue& out_queue);
};

}  // namespace rendering

}  // namespace glab
