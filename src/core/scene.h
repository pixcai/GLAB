#pragma once

#include <vector>
#include <unordered_map>

#include "rendering.h"
#include "world.h"

GLAB_NAMESPACE_BEGIN()

class Object;

class Scene {
public:
    Object createObject();
    void destroyObject(Object& object);

    std::vector<RenderItem>& collectRenderItem();

private:
    World m_world;
    std::vector<RenderItem> m_render_items;
    std::unordered_map<std::uint32_t, Entity> m_entity_map;

    friend class Object;
};

class Object {
public:
    Object() = delete;

    explicit Object(Scene* scene) : m_scene(scene) {
        m_entity = m_scene->m_world.createEntity();
        m_scene->m_entity_map[m_entity.id] = m_entity;
    }

    template <typename T, typename... Args>
    T& add(Args&&... args) {
        return m_scene->m_world.addComponent<T>(m_entity, std::forward<Args>(args)...);
    };

    template <typename T>
    void remove() {
        m_scene->m_world.removeComponent<T>(m_entity);
    }

    template <typename T>
    T* get() noexcept {
        return m_scene->m_world.getComponent<T>(m_entity);
    }

    template <typename T>
    bool has() noexcept {
        return m_scene->m_world.hasComponent<T>(m_entity);
    }

    void destroy() {
        m_scene->m_world.destroyEntity(m_entity);
        m_scene->m_entity_map.erase(m_entity.id);
    }

private:
    Scene* m_scene;
    Entity m_entity;
};

GLAB_NAMESPACE_END()
