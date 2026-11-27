#include "compositor.h"
#include "scene/scene.h"

namespace glab::rendering {

void Compositor::BeginFrame() {
    m_queue.opaque.clear();
    m_queue.transparent.clear();
    m_mesh_renderer.BeginFrame();
}

void Compositor::Render(scene::Scene& scene) {
    m_collector.Collect(scene, m_queue);

    auto& camera = scene.GetActiveCamera();

    for (auto& task : m_queue.opaque) {
        m_mesh_renderer.Render(task, camera);
    }
    for (auto& task : m_queue.transparent) {
        m_mesh_renderer.Render(task, camera);
    }
}

void Compositor::EndFrame() { m_mesh_renderer.EndFrame(); }

}  // namespace glab::rendering
