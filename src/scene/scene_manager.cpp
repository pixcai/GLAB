#include "scene_manager.h"

#include <memory>

namespace glab::scene {

Scene* SceneManager::CreateScene() {
    auto scene = std::make_unique<Scene>();
    auto id = scene->id;
    m_scenes.try_emplace(id, std::move(scene));
    return m_scenes[id].get();
}

Scene* SceneManager::GetActiveScene() {
    if (auto it = m_scenes.find(m_active_scene_id); it != m_scenes.end()) {
        return it->second.get();
    }
    return nullptr;
}

}  // namespace glab::scene
