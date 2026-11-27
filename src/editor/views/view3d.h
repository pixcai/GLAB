#pragma once

#include "editor/editor_context.h"
#include "editor/editor_ui.h"
#include "rendering/compositor.h"
#include "rendering/shader_manager.h"

namespace glab::editor {

struct View3D : public EditorUI {
    View3D(EditorContext& context);
    ~View3D();

    void Render(EditorContext& context) override;

private:
    rendering::ShaderManager m_shader_manager;
    rendering::RenderContext m_render_context;
    rendering::Compositor m_compositor;
};

}  // namespace glab::editor
