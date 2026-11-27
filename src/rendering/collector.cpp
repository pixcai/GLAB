#include "collector.h"
#include "render_queue.h"
#include "rendering/material.h"
#include "scene/components/mesh_component.h"
#include "scene/scene.h"

#include <vector>

namespace glab::rendering {

void Collector::Collect(scene::Scene& scene, RenderQueue& out_queue) {
    MaterialID material_id;
    std::vector<RenderItem> items;

    for (auto& [_, node] : scene.nodes) {
        if (auto component = node.Get<scene::MeshComponent>(); component != nullptr) {
            material_id = component->material_id;
            items.emplace_back(component->mesh_id, node.transform.world_matrix);
        }
    }
    out_queue.opaque.emplace_back(material_id, std::move(items));
}

}  // namespace glab::rendering
