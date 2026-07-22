#include "scene.h"

GLAB_NAMESPACE_BEGIN()

Object Scene::createObject() { return Object(this); }

void Scene::destroyObject(Object& object) { object.destroy(); }

std::vector<RenderItem>& Scene::collectRenderItem() {
    m_render_items.clear();
    for (auto& [_, entity] : m_entity_map) {
        auto mesh_renderer = m_world.getComponent<MeshRenderer>(entity);
        if (!mesh_renderer) {
            continue;
        }
        RenderItem render_item{};
        render_item.mesh_handle = mesh_renderer->mesh_handle;
        m_render_items.push_back(render_item);
    }
    return m_render_items;
}

GLAB_NAMESPACE_END()
