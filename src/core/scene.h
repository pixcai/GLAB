#pragma once

#include <functional>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "common.h"

GLAB_NAMESPACE_BEGIN()

class Entity {
public:
    Entity();
    Entity(const std::string& name);

    template <typename T>
    T* get() const noexcept {
        if (m_component_map.contains(typeid(T))) {
            return static_cast<T*>(m_component_map.at(typeid(T)).get());
        }
        return nullptr;
    }

    template <typename T, typename... Args>
    void add(Args&&... args) {
        m_component_map.try_emplace(typeid(T), std::make_unique<T>(std::forward<Args>(args)...));
    }

    template <typename T>
    void remove() {
        m_component_map.erase(typeid(T));
    }

public:
    const uint32_t id;
    std::string name;

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_component_map;
};

class Scene {
public:
    void add(std::shared_ptr<Entity> entity);
    void remove(uint32_t id);
    void forEach(std::function<void(Entity*)> callback);

private:
    std::unordered_map<uint32_t, std::shared_ptr<Entity>> m_entity_map;
};

GLAB_NAMESPACE_END()
