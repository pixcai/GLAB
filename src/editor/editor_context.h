#pragma once

namespace glab {

class EventManager;

namespace scene {

class SceneManager;

}

namespace rendering {

class Compositor;

}

namespace editor {

struct EditorContext {
    EventManager* event_manager{nullptr};
    scene::SceneManager* scene_manager{nullptr};
    rendering::Compositor* compositor{nullptr};
};

}  // namespace editor

}  // namespace glab
