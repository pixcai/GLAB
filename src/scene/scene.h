#pragma once

#include "node.h"
#include "rendering/render_queue.h"

#include <glm/glm.hpp>

namespace glab::scene {

class Scene {
public:
    inline static NodeID next_node_id = 1;

public:
    Scene();
    ~Scene() = default;

    std::shared_ptr<Node> GetRoot() const { return m_root; }

    std::shared_ptr<Node> MakeNode();
    void AddNode(std::shared_ptr<Node> node);
    void RemoveNode(std::shared_ptr<Node> node);

    rendering::RenderQueue GetRenderItems() const;

public:
    glm::vec4 background_color{};

private:
    void CollectRenderItems(std::shared_ptr<Node> node, rendering::RenderQueue& queue) const;

private:
    std::shared_ptr<Node> m_root;
    Storage m_storage;
};

}  // namespace glab::scene
