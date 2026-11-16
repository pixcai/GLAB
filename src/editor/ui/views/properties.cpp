#include "editor/editor_context.h"
#include "properties.h"

#include <imgui.h>

namespace glab::editor::ui {

void Properties::Render(editor::EditorContext& editor_context) {
    if (ImGui::Begin("Properties", &visible)) {
    }
    ImGui::End();
}

}  // namespace glab::editor::ui
