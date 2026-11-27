#pragma once

namespace glab {

class EventManager;

namespace scene {

class SceneManager;

}

namespace editor {

struct EditorContext {
    EventManager* event_manager{nullptr};
    scene::SceneManager* scene_manager{nullptr};
};

}  // namespace editor

}  // namespace glab
