#include "editor_shell.h"

#include <format>

#include <glad/gl.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace glab {

EditorShell::EditorShell(EventManager* event_manager) : m_event_manager(event_manager), m_editor(event_manager) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 1920, 1080);
}

EditorShell::~EditorShell() {}

void EditorShell::BeginFrame() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_editor.BeginFrame();
}

void EditorShell::Render() {
    RenderMainMenuBar();
    RenderStatusBar();
    RenderDockSpace();
    m_editor.Render();
}

void EditorShell::EndFrame() { m_editor.EndFrame(); }

void EditorShell::RenderMainMenuBar() {
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

void EditorShell::RenderStatusBar() {
    auto viewport = ImGui::GetMainViewport();
    auto padding = ImGui::GetStyle().WindowPadding;
    auto height = ImGui::GetTextLineHeight() + padding.y * 2.0f;

    ImGui::SetNextWindowPos({0.0f, viewport->Size.y - height});
    ImGui::SetNextWindowSize({viewport->Size.x, height});
    viewport->WorkSize.y -= height;

    ImGui::Begin("StatusBar", nullptr,
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

void EditorShell::RenderDockSpace() {
    auto viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{});
    ImGui::Begin("DockSpace", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus);
    ImGui::DockSpace(ImGui::GetID("Main"), ImGui::GetContentRegionAvail());
    ImGui::End();
    ImGui::PopStyleVar();
}

}  // namespace glab
