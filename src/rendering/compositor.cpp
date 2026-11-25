#include "compositor.h"
#include "scene/scene.h"

namespace glab::rendering {

void Compositor::BeginFrame() {}

void Compositor::Render(scene::Scene& scene) { m_collector.Collect(scene, m_queue); }

void Compositor::EndFrame() {}

}  // namespace glab::rendering
