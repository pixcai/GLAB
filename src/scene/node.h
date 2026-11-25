#pragma once

#include "core/id.h"

#include <any>
#include <typeindex>
#include <unordered_map>

namespace glab::scene {

class Node;

using NodeID = core::ID<Node>;

struct Node {
    NodeID id;
    NodeID parent;
    std::vector<NodeID> children;
    std::unordered_map<std::type_index, std::any> components;

    template <typename Component>
    void Add(Component&& component) {
        components.insert_or_assign(typeid(Component), std::move(component));
    }

    template <typename Component>
    void Remove() {
        components.erase(typeid(Component));
    }

    template <typename Component>
    Component* Get() {
        if (auto it = components.find(typeid(Component)); it != components.end()) {
            return &std::any_cast<Component>(it->second);
        }
        return nullptr;
    }
};

}  // namespace glab::scene
