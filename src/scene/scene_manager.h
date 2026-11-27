#pragma once

#include "core/flat_hash_map.h"
#include "scene.h"

namespace glab::scene {

class SceneManager {
public:
    Scene& CreateScene();
    Scene& GetActiveScene();
    void SetActiveScene(SceneID id);

private:
    SceneID m_active_scene_id;
    core::FlatHashMap<SceneID, Scene> m_scenes;
};

}  // namespace glab::scene
