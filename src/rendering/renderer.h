#pragma once

#include "buffer_object.h"
#include "render_queue.h"
#include "scene/camera.h"

namespace glab::rendering {

class MeshRenderer {
public:
    MeshRenderer();
    ~MeshRenderer() = default;

    void BeginFrame();
    void Render(const RenderTask& task, const scene::Camera& camera);
    void EndFrame();

private:
    void DrawItem(const RenderItem& item, const scene::Camera& camera);

    RenderBufferGroup m_buffer_group;
};

}  // namespace glab::rendering
