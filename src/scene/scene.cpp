#include "camera.h"
#include "node.h"
#include "scene.h"

#include <spdlog/spdlog.h>

namespace glab::scene {

Scene::Scene() : id(id_pool.Allocate()), root(CreateNode()) {
    spdlog::debug("Scene(index={}, generation={})", id.index, id.generation);
    root.Add<Camera>({});
    SetActiveCamera(root.Get<Camera>());
}

Scene::~Scene() {
    spdlog::debug("~Scene(index={}, generation={})", id.index, id.generation);
    id_pool.Deallocate(id);
}

Node Scene::CreateNode() { return {}; }

void Scene::AddNode(Node&& node) {
    if (!node.id.IsValid() || nodes.Contains(node.id)) {
        return;
    }
    spdlog::debug("AddNode(index={}, generation={})", node.id.index, node.id.generation);
    root.children.push_back(node.id);
    node.parent = root.id;
    nodes.Insert(node.id, std::move(node));
}

void Scene::RemoveNode(NodeID id) {
    if (auto node = nodes.Get(id); node != nullptr) {
        if (node->parent == root.id) {
            std::erase(root.children, id);
        } else {
            auto parent = nodes.Get(node->parent);
            std::erase(parent->children, id);
        }
        node->parent.Reset();
    }
    nodes.Erase(id);
}

void Scene::SetActiveCamera(Camera* camera) {
    if (!camera) {
        active_camera = root.Get<Camera>();
    } else {
        active_camera = camera;
    }
}

}  // namespace glab::scene
