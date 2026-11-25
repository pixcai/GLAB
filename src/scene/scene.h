#pragma once

#include "core/flat_hash_map.h"
#include "core/id.h"
#include "node.h"

namespace glab::scene {

class Scene;

using SceneID = core::ID<Scene>;

class Scene {
public:
    Scene();
    ~Scene() = default;

    Node CreateNode();
    void AddNode(Node&& node);
    void RemoveNode(NodeID id);

    SceneID id;
    Node root;
    core::FlatHashMap<NodeID, Node> nodes;
};

}  // namespace glab::scene
