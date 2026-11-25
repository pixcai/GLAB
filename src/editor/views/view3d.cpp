#include "editor/editor_ui.h"
#include "rendering/compositor.h"
#include "scene/scene_manager.h"
#include "view3d.h"

#include <imgui.h>

namespace glab::editor {

View3D::View3D(EditorContext& context) : EditorUI(context) {}

View3D::~View3D() {}

void View3D::Render(EditorContext& context) {
    if (ImGui::Begin("View3D", &visible)) {
        if (auto scene = context.scene_manager->GetActiveScene(); scene != nullptr) {
            context.compositor->Render(*scene);
        }
    }
    ImGui::End();
}

}  // namespace glab::editor
