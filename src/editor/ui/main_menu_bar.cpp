#include "main_menu_bar.h"

#include <imgui.h>

namespace glab::editor::ui {

void MainMenuBar::Render(editor::EditorContext& editor_context) {
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {0.0f, 8.0f});

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Quit", "Ctrl+Q")) {
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    ImGui::PopStyleVar();
}

}  // namespace glab::editor::ui
