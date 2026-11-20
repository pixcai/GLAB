#pragma once

#include "core/event_manager.h"
#include "scene/scene.h"

namespace glab::editor {

struct EditorContext {
    core::EventManager event_manager;
    scene::Scene* scene{nullptr};
};

}  // namespace glab::editor
