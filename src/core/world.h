#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "common.h"

GLAB_NAMESPACE_BEGIN()

class EntityManager {
public:
    Entity create() {
        std::uint32_t id;

        if (!m_free_ids.empty()) {
            id = m_free_ids.back();
            m_free_ids.pop_back();
        } else {
            id = m_generations.size();
            m_generations.push_back(0);
        }
        return {id, m_generations[id]};
    }

    void destroy(Entity entity) {
        if (!alive(entity)) return;

        m_generations[entity.id]++;
        m_free_ids.push_back(entity.id);
    }

    bool alive(Entity entity) noexcept {
        return entity.id < m_generations.size() && m_generations[entity.id] == entity.generation;
    }

private:
    std::vector<std::uint32_t> m_free_ids;
    std::vector<std::uint32_t> m_generations;
};

struct _IComponentStorage {
    virtual ~_IComponentStorage() = default;
    virtual void remove(Entity entity) = 0;
};

template <ComponentLike Component>
class _ComponentStorage : public _IComponentStorage {
public:
    Component* get(Entity entity) noexcept {
        if (has(entity)) {
            return &m_components[m_index_map.at(entity.id)];
        }
        return nullptr;
    }

    bool has(Entity entity) noexcept { return m_index_map.contains(entity.id); }

    void add(Entity entity, Component component) {
        if (entity.id == Entity::kInvalidID || has(entity)) return;

        m_components.push_back(std::move(component));
        m_index_map[entity.id] = m_components.size() - 1;
    }

    void remove(Entity entity) override {
        if (!has(entity)) return;

        auto index = m_index_map.at(entity.id);
        auto last = m_components.size() - 1;
        m_components[index] = m_components[last];
        m_components.pop_back();
        m_index_map.erase(entity.id);
    }

private:
    std::vector<Component> m_components;
    std::unordered_map<std::uint32_t, std::size_t> m_index_map;
};

class ComponentManager {
public:
    template <ComponentLike Component>
    _ComponentStorage<Component>& getStorage() {
        auto type = std::type_index(typeid(Component));

        if (!m_storage_map.contains(type)) {
            m_storage_map[type] = std::make_unique<_ComponentStorage<Component>>();
        }
        return *static_cast<_ComponentStorage<Component>*>(m_storage_map.at(type).get());
    }

    void removeAll(Entity entity) {
        for (auto& [_, storage] : m_storage_map) {
            storage->remove(entity);
        }
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<_IComponentStorage>> m_storage_map;
};

class World {
public:
    Entity createEntity() { return m_entity_manager.create(); }

    void destroyEntity(Entity entity) {
        m_component_manager.removeAll(entity);
        m_entity_manager.destroy(entity);
    }

    template <ComponentLike Component, typename... Args>
    Component* addComponent(Entity entity, Args&&... args) {
        if (entity.id == Entity::kInvalidID) {
            return nullptr;
        }
        auto& storage = m_component_manager.getStorage<Component>();
        storage.add(entity, Component(std::forward<Args>(args)...));
        return storage.get(entity);
    };

    template <ComponentLike Component>
    void removeComponent(Entity entity) {
        m_component_manager.getStorage<Component>().remove(entity);
    }

    template <ComponentLike Component>
    Component* getComponent(Entity entity) noexcept {
        return m_component_manager.getStorage<Component>().get(entity);
    }

    template <ComponentLike Component>
    bool hasComponent(Entity entity) noexcept {
        return m_component_manager.getStorage<Component>().has(entity);
    }

private:
    EntityManager m_entity_manager;
    ComponentManager m_component_manager;
};

GLAB_NAMESPACE_END()
