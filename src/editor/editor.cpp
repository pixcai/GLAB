#include "editor.h"
#include "editor/views/outliner.h"
#include "editor/views/properties.h"
#include "editor/views/view3d.h"
#include "resource_factory.h"
#include "scene/components/mesh_component.h"

namespace glab::editor {

Editor::Editor(EventManager* event_manager) : m_context(event_manager, &m_scene_manager, &m_compositor) {
    auto scene = m_scene_manager.CreateScene();
    auto node = scene.CreateNode();

    node.Add<scene::MeshComponent>({ResourceFactory::CreateCube(2.0f)});
    scene.AddNode(std::move(node));
    m_scene_manager.SetActiveScene(scene.id);

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
