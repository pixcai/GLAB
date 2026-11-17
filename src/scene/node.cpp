#include "node.h"

namespace glab::scene {

Node::Node(NodeID id, Storage& storage) : m_id(id), m_storage(storage) {}

void Node::AddChild(std::shared_ptr<Node> child) {
    if (m_children.contains(child->m_id)) {
        return;
    }
    if (child->m_parent) {
        child->m_parent->RemoveChild(child);
    }
    m_children.emplace(child->m_id, child);
    child->m_parent = shared_from_this();
}

void Node::RemoveChild(std::shared_ptr<Node> child) {
    if (!m_children.contains(child->m_id)) {
        return;
    }
    m_children.erase(child->m_id);
    child->m_parent = nullptr;
}

}  // namespace glab::scene
