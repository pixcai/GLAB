#include "editor/editor_ui.h"
#include "rendering/compositor.h"
#include "rendering/framebuffer.h"
#include "scene/scene_manager.h"
#include "view3d.h"

#include <memory>

#include <imgui.h>

namespace glab::editor {

namespace {

GLsizei last_width = 0;
GLsizei last_height = 0;

}  // namespace

View3D::View3D(EditorContext& context) : EditorUI(context) {
    m_shader_manager.Set("mesh", {{GL_VERTEX_SHADER, "mesh.vert"}, {GL_FRAGMENT_SHADER, "mesh.frag"}});

    m_render_context.shader_manager = &m_shader_manager;
    m_compositor = std::make_unique<rendering::Compositor>(m_render_context);
}

View3D::~View3D() {}

void View3D::Render(EditorContext& context) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if (ImGui::Begin("View3D", &visible)) {
        auto size = ImGui::GetContentRegionAvail();
        auto width = static_cast<GLsizei>(size.x);
        auto height = static_cast<GLsizei>(size.y);

        if (!m_framebuffer) {
            m_framebuffer = std::make_unique<rendering::Framebuffer>(width, height);
            m_render_context.framebuffer = m_framebuffer.get();
        }
        auto& scene = context.scene_manager->GetActiveScene();
        if (width != last_width || height != last_height) {
            last_width = width;
            last_height = height;

            auto& camera = scene.GetActiveCamera();
            camera.width = width;
            camera.height = height;
            camera.updateProjectionMatrix();
            if (m_framebuffer) {
                m_framebuffer->Resize(width, height);
            }
        }
        m_compositor->BeginFrame();
        m_compositor->Render(scene);
        m_compositor->EndFrame();
        ImGui::Image(m_render_context.framebuffer->color_texture.GetID(), size, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

}  // namespace glab::editor
