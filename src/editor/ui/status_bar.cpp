#include "editor/editor_context.h"
#include "status_bar.h"

#include <format>
#include <string>

#include <imgui.h>

namespace glab::editor::ui {

void StatusBar::Render(editor::EditorContext& editor_context) {
    auto viewport = ImGui::GetMainViewport();
    auto padding = ImGui::GetStyle().WindowPadding;
    auto height = ImGui::GetTextLineHeight() + padding.y * 2.0f;

    ImGui::SetNextWindowPos({0.0f, viewport->Size.y - height});
    ImGui::SetNextWindowSize({viewport->Size.x, height});
    viewport->WorkSize.y -= height;

    ImGui::Begin("StatusBar", &visible,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking);
    ImGui::Text("Ready");

    auto info = std::format("FPS: {:.0f}", ImGui::GetIO().Framerate);
    auto width = ImGui::CalcTextSize(info.c_str()).x;

    ImGui::SameLine();
    ImGui::SetCursorPosX(viewport->Size.x - padding.x - width);
    ImGui::Text("%s", info.c_str());
    ImGui::End();
}

}  // namespace glab::editor::ui
