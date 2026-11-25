#include "scene_manager.h"

#include <memory>

namespace glab::scene {

Scene* SceneManager::CreateScene() {
    auto scene = std::make_unique<Scene>();
    m_scenes.try_emplace(scene->id, std::move(scene));
    return m_scenes[scene->id].get();
}

Scene* SceneManager::GetActiveScene() {
    if (auto it = m_scenes.find(m_active_scene_id); it != m_scenes.end()) {
        return it->second.get();
    }
    return nullptr;
}

}  // namespace glab::scene
