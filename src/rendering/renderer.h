#pragma once

#include "buffer_object.h"
#include "render_queue.h"
#include "scene/camera.h"
#include "shader_manager.h"

namespace glab::rendering {

struct RenderContext {
    ShaderManager* shader_manager{nullptr};
};

class MeshRenderer {
public:
    MeshRenderer(RenderContext& context);
    ~MeshRenderer() = default;

    void BeginFrame();
    void Render(const RenderTask& task, const scene::Camera& camera);
    void EndFrame();

private:
    void DrawItem(const RenderItem& item, const scene::Camera& camera);

    RenderContext& m_context;
    RenderBufferGroup m_buffer_group;
};

}  // namespace glab::rendering
