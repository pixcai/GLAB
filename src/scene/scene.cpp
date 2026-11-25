#include "node.h"
#include "scene.h"

#include <spdlog/spdlog.h>

namespace glab::scene {

Scene::Scene() : root(CreateNode()) {}

Node Scene::CreateNode() {
    spdlog::debug("Create node");
    return {};
}

void Scene::AddNode(Node&& node) { nodes.Insert(node.id, std::move(node)); }

void Scene::RemoveNode(NodeID id) { nodes.Erase(id); }

}  // namespace glab::scene
