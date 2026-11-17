#include "rendering/render_queue.h"
#include "scene.h"

#include <spdlog/spdlog.h>

namespace glab::scene {

Scene::Scene() : m_root(MakeNode()) {}

std::shared_ptr<Node> Scene::MakeNode() {
    spdlog::debug("Making node");
    return std::shared_ptr<Node>(new Node(Scene::next_node_id++, m_storage));
}

void Scene::AddNode(std::shared_ptr<Node> node) { m_root->AddChild(node); }

void Scene::RemoveNode(std::shared_ptr<Node> node) { m_root->RemoveChild(node); }

rendering::RenderQueue Scene::GetRenderItems() const {
    rendering::RenderQueue queue{};

    CollectRenderItems(m_root, queue);
    return queue;
}

void Scene::CollectRenderItems(std::shared_ptr<Node> node, rendering::RenderQueue& queue) const {
    for (auto& [_, child] : node->m_children) {
        queue.meshes.emplace_back();
    }
    for (auto& [_, child] : node->m_children) {
        CollectRenderItems(child, queue);
    }
}

}  // namespace glab::scene
