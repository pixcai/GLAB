#include "dock_space.h"
#include "editor/editor_context.h"

#include <imgui.h>

namespace glab::editor::ui {

void DockSpace::Render(editor::EditorContext& editor_context) {
    auto viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{});
    ImGui::Begin("DockSpace", &visible,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus);
    ImGui::DockSpace(ImGui::GetID("EditorDockSpace"), ImGui::GetContentRegionAvail());
    ImGui::End();
    ImGui::PopStyleVar();
}

}  // namespace glab::editor::ui
