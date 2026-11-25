#include "outliner.h"

#include <imgui.h>

namespace glab::editor {

void Outliner::Render(EditorContext& context) {
    if (ImGui::Begin("Outliner", &visible)) {
    }
    ImGui::End();
}

}  // namespace glab::editor
