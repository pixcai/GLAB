#include "editor/editor_ui.h"
#include "rendering/compositor.h"
#include "scene/scene_manager.h"
#include "view3d.h"

#include <imgui.h>

namespace glab::editor {

View3D::View3D(EditorContext& context)
    : EditorUI(context), m_shader_manager(), m_render_context(&m_shader_manager), m_compositor(m_render_context) {
    m_shader_manager.Set("mesh", {{GL_VERTEX_SHADER, "mesh.vert"}, {GL_FRAGMENT_SHADER, "mesh.frag"}});
}

View3D::~View3D() {}

void View3D::Render(EditorContext& context) {
    if (ImGui::Begin("View3D", &visible)) {
        m_compositor.Render(context.scene_manager->GetActiveScene());
    }
    ImGui::End();
}

}  // namespace glab::editor
