#pragma once

#include "scene.h"

#include <memory>
#include <unordered_map>

namespace glab::scene {

class SceneManager {
public:
    Scene* CreateScene();
    Scene* GetActiveScene();

private:
    SceneID m_active_scene_id;
    std::unordered_map<SceneID, std::unique_ptr<Scene>> m_scenes;
};

}  // namespace glab::scene
