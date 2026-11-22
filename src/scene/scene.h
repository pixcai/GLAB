#pragma once

#include "core/id.h"
#include "node.h"
#include "rendering/render_queue.h"

namespace glab::scene {

class Scene;

using SceneID = core::ID<Scene>;

class Scene {
public:
    Scene();
    ~Scene() = default;

    SceneID id;

    std::shared_ptr<Node> GetRoot() const { return m_root; }

    std::shared_ptr<Node> MakeNode();
    void AddNode(std::shared_ptr<Node> node);
    void RemoveNode(std::shared_ptr<Node> node);

    rendering::RenderQueue GetRenderItems() const;

private:
    void CollectRenderItems(std::shared_ptr<Node> node, rendering::RenderQueue& queue) const;

private:
    std::shared_ptr<Node> m_root;
    Storage m_storage;
};

}  // namespace glab::scene
