#include <cstdlib>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "gl.h"
#include "gui.h"
#include "logger.h"

constexpr int GLAB_WIDTH = 1000;
constexpr int GLAB_HEIGHT = 800;

void onErrorCallback(int error, const char* description) {
    LOG_ERROR("({}) {}", error, description);
}

int main() {
    GLAB_INIT_LOGGER();
    glfwSetErrorCallback(onErrorCallback);
    if (glfwInit() != GLFW_TRUE) {
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLAB_GL_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLAB_GL_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    float dpi = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    GLFWwindow* window = glfwCreateWindow((float)(dpi * GLAB_WIDTH), (float)(dpi * GLAB_HEIGHT),
                                          "GLAB", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    GLAB_LOAD_GL();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(dpi);
    style.FontScaleDpi = dpi;
    style.FramePadding = ImVec2(8.0f, 8.0f);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(GLAB_GLSL_VERSION);

    GUI gui{window};

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        gui.render();
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
