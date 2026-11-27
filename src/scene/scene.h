#pragma once

#include "camera.h"
#include "core/flat_hash_map.h"
#include "core/id.h"
#include "node.h"

namespace glab::scene {

class Scene;

using SceneID = core::ID<Scene>;

class Scene {
public:
    static inline core::IDPool<Scene> id_pool;

    Scene();
    ~Scene();

    Node CreateNode();
    void AddNode(Node&& node);
    void RemoveNode(NodeID id);

    std::size_t GetNodeCount() const { return nodes.Size(); }
    Camera& GetActiveCamera() { return *root.Get<Camera>(); }
    void SetActiveCamera(Camera* camera);

    SceneID id;
    Node root;
    core::FlatHashMap<NodeID, Node> nodes;

    Camera* active_camera;
};

}  // namespace glab::scene
