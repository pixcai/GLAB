#include "gui.h"

#include <cstdio>
#include <memory>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>

#include "core/renderer.h"
#include "core/scene.h"

static std::unique_ptr<GLAB_NAMESPACE::Renderer> renderer;
static std::unique_ptr<GLAB_NAMESPACE::Scene> scene;

GUI::GUI(GLFWwindow* window) {
    renderer = std::make_unique<GLAB_NAMESPACE::Renderer>();
    scene = std::make_unique<GLAB_NAMESPACE::Scene>();

    auto object = scene->createObject();
    object.add<GLAB_NAMESPACE::MeshRenderer>();
    scene->addObject(object);
}

void GUI::render() {
    auto render_items = scene->collectRenderItems();
    renderer->setClearColor(scene->clear_color);
    renderer->render(render_items);

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGuiID dockspace = ImGui::GetID("DockSpace");

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Root", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
                     ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_MenuBar);
    renderMainMenuBar();
    ImGui::DockSpace(dockspace);
    ImGui::End();
    ImGui::PopStyleVar();
    renderStatusBar();

    renderWorkspace();
    renderInspector();

    static bool initialized{false};

    if (!initialized) {
        initLayout();
        initialized = true;
    }
}

void GUI::renderMainMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void GUI::renderStatusBar() {
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + viewport->Size.y - 32.0f));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, 32.0f));

    char info[32];
    snprintf(info, sizeof(info), "(%d, %d) | FPS %d", (int)io.MousePos.x, (int)io.MousePos.y,
             (int)io.Framerate);

    float info_width = ImGui::CalcTextSize(info).x;

    ImGui::Begin("StatusBar", nullptr,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking |
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPosX(viewport->Pos.x + viewport->Size.x - style.WindowPadding.x - info_width);
    ImGui::Text("%s", info);
    ImGui::End();
}

void GUI::initLayout() {
    ImGuiID dockspace = ImGui::GetID("DockSpace");
    ImGuiID workspace, inspector;

    ImGui::DockBuilderRemoveNode(dockspace);
    ImGui::DockBuilderAddNode(dockspace, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspace, ImGui::GetMainViewport()->Size);

    ImGui::DockBuilderSplitNode(dockspace, ImGuiDir_Left, 0.75f, &workspace, &inspector);
    ImGui::DockBuilderDockWindow("Workspace", workspace);
    ImGui::DockBuilderDockWindow("Inspector", inspector);
    ImGui::DockBuilderFinish(dockspace);
}

void GUI::renderWorkspace() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Workspace", nullptr, ImGuiWindowFlags_MenuBar);

    ImGui::BeginMenuBar();
    ImGui::EndMenuBar();

    auto size = ImGui::GetContentRegionAvail();
    renderer->resize(static_cast<int>(size.x), static_cast<int>(size.y));
    ImGui::Image((ImTextureID)(std::intptr_t)renderer->texture(), size, ImVec2(0.0f, 1.0f),
                 ImVec2(1.0f, 0.0f));

    ImGui::End();
    ImGui::PopStyleVar();
}

void GUI::renderInspector() {
    ImGui::Begin("Inspector");
    ImGui::End();
}
