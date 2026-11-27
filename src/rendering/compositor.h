#pragma once

#include "collector.h"
#include "render_queue.h"
#include "renderer.h"

namespace glab {

namespace scene {

class Scene;

}

namespace rendering {

class Compositor {
public:
    Compositor(RenderContext& context);
    ~Compositor() = default;

    void BeginFrame();
    void Render(scene::Scene& scene);
    void EndFrame();

private:
    RenderQueue m_queue;
    Collector m_collector;
    MeshRenderer m_mesh_renderer;
};

}  // namespace rendering

}  // namespace glab
