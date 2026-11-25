#include "properties.h"

#include <imgui.h>

namespace glab::editor {

void Properties::Render(EditorContext& context) {
    if (ImGui::Begin("Properties", &visible)) {
    }
    ImGui::End();
}

}  // namespace glab::editor
