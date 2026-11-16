#include "config/config.h"
#include "editor.h"
#include "editor/ui/main_menu_bar.h"
#include "editor/ui/views/outliner.h"
#include "editor/ui/views/properties.h"
#include "editor/ui/views/view3d.h"
#include "platform/window.h"

#include <glad/gl.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace glab::editor {

static bool g_initialized = false;

void Init(platform::Window* window) {
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGuiStyle& style = ImGui::GetStyle();
    float scale = platform::GetContentScale(window);
    style.ScaleAllSizes(scale);
    style.FontScaleDpi = scale;

    ImGui_ImplGlfw_InitForOpenGL(platform::GetNativeWindow(window), true);
    ImGui_ImplOpenGL3_Init(config::kGLSLVersionString.data());

    g_initialized = true;
}

void Shutdown() {
    if (g_initialized) {
        g_initialized = false;
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}

Editor::Editor(platform::Window* window, event::EventEmitter& event_emitter)
    : m_context({.event_emitter = event_emitter, .window = window}) {
    m_widgets.emplace_back(std::make_unique<ui::MainMenuBar>());
    m_widgets.emplace_back(std::make_unique<ui::View3D>());
    m_widgets.emplace_back(std::make_unique<ui::Outliner>());
    m_widgets.emplace_back(std::make_unique<ui::Properties>());
}

Editor::~Editor() {}

void Editor::BeginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Editor::Render() {
    for (auto& widget : m_widgets) {
        widget->Render(m_context);
    }
}

void Editor::EndFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}  // namespace glab::editor
