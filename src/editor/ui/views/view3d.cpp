#include "editor/editor_context.h"
#include "view3d.h"

#include <imgui.h>

namespace glab::editor::ui {

void View3D::Render(editor::EditorContext& editor_context) {
    if (ImGui::Begin("View3D", &visible)) {
    }
    ImGui::End();
}

}  // namespace glab::editor::ui
