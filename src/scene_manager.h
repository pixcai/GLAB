#pragma once

#include "scene/scene.h"

#include <memory>
#include <unordered_map>

namespace glab {

class SceneManager {
public:
    scene::Scene* CreateScene();
    scene::Scene* GetActiveScene();

private:
    scene::SceneID m_active_scene_id;
    std::unordered_map<scene::SceneID, std::unique_ptr<scene::Scene>> m_scenes;
};

}  // namespace glab
