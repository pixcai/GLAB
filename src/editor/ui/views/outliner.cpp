#include "editor/editor_context.h"
#include "outliner.h"

#include <imgui.h>

namespace glab::editor::ui {

void Outliner::Render(editor::EditorContext& editor_context) {
    if (ImGui::Begin("Outliner", &visible)) {
    }
    ImGui::End();
}

}  // namespace glab::editor::ui
