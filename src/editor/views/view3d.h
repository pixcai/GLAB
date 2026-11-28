#pragma once

#include "editor/editor_context.h"
#include "editor/editor_ui.h"
#include "rendering/compositor.h"
#include "rendering/framebuffer.h"
#include "rendering/shader_manager.h"

#include <memory>

namespace glab::editor {

struct View3D : public EditorUI {
    View3D(EditorContext& context);
    ~View3D();

    void Render(EditorContext& context) override;

private:
    rendering::ShaderManager m_shader_manager;
    rendering::RenderContext m_render_context;
    std::unique_ptr<rendering::Compositor> m_compositor;
    std::unique_ptr<rendering::Framebuffer> m_framebuffer;
};

}  // namespace glab::editor
