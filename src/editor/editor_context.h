#pragma once

#include "event_manager.h"
#include "scene/scene.h"

namespace glab::editor {

struct EditorContext {
    EventManager event_manager;
    scene::Scene* scene{nullptr};
};

}  // namespace glab::editor
