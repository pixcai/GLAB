#include "editor.h"
#include "editor/views/outliner.h"
#include "editor/views/properties.h"
#include "editor/views/view3d.h"

namespace glab::editor {

Editor::Editor(EventManager* event_manager) : m_context(event_manager, &m_scene_manager, &m_compositor) {
    m_scene_manager.CreateScene();

    m_widgets.emplace_back(std::make_unique<View3D>(m_context));
    m_widgets.emplace_back(std::make_unique<Outliner>());
    m_widgets.emplace_back(std::make_unique<Properties>());
}

Editor::~Editor() {}

void Editor::BeginFrame() {}

void Editor::Render() {
    for (auto& widget : m_widgets) {
        widget->Render(m_context);
    }
}

void Editor::EndFrame() {}

}  // namespace glab::editor
