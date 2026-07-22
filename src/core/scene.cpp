#include "scene.h"

#include <atomic>

GLAB_NAMESPACE_BEGIN()

static std::atomic_uint32_t next_entity_id{1};

Entity::Entity() : Entity("Object" + std::to_string(next_entity_id)) {}

Entity::Entity(const std::string& name) : id(next_entity_id), name(name) { next_entity_id++; }

void Scene::add(std::shared_ptr<Entity> entity) { m_entity_map.try_emplace(entity->id, entity); }

void Scene::remove(uint32_t id) { m_entity_map.erase(id); }

void Scene::forEach(std::function<void(Entity*)> callback) {
    for (auto& [_, entity] : m_entity_map) {
        callback(entity.get());
    }
}

GLAB_NAMESPACE_END()
