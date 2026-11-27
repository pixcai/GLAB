#include "scene/scene.h"
#include "scene_manager.h"

namespace glab::scene {

Scene& SceneManager::CreateScene() {
    scene::Scene scene;
    auto id = scene.id;

    m_scenes.Insert(id, std::move(scene));
    return *m_scenes.Get(id);
}

Scene& SceneManager::GetActiveScene() { return *m_scenes.Get(m_active_scene_id); }

void SceneManager::SetActiveScene(SceneID id) { m_active_scene_id = id; }

}  // namespace glab::scene
