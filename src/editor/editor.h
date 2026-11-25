#pragma once

#include "editor_context.h"
#include "editor_ui.h"
#include "rendering/compositor.h"
#include "resource_manager.h"
#include "scene/scene_manager.h"

#include <memory>
#include <vector>

namespace glab::editor {

class Editor {
public:
    Editor(EventManager* event_manager);
    ~Editor();

    void BeginFrame();
    void Render();
    void EndFrame();

private:
    ResourceManager m_resource_manager;
    scene::SceneManager m_scene_manager;
    rendering::Compositor m_compositor;
    EditorContext m_context;
    std::vector<std::unique_ptr<EditorUI>> m_widgets;
};

}  // namespace glab::editor
