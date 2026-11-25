#include "editor_shell.h"
#include "engine.h"

#include <memory>
#include <stdexcept>

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>

namespace glab {

namespace {

void OnError(int code, const char* description) { spdlog::error("GLFW ({}): {}", code, description); }

}  // namespace

Engine::Engine(const char* title, int width, int height) {
    glfwSetErrorCallback(OnError);
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    gladLoaderLoadGL();

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    float scale = ImGui_ImplGlfw_GetContentScaleForWindow(m_window);
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(scale);
    style.FontScaleDpi = scale;

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 410 core");

    m_editor_shell = std::make_unique<EditorShell>(&m_event_manager);
}

Engine::~Engine() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Engine::Run() {
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        m_editor_shell->BeginFrame();
        m_editor_shell->Render();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_window);
        m_editor_shell->EndFrame();
    }
}

}  // namespace glab
