#pragma once

#include "core/event/event_emitter.h"
#include "platform/window.h"

namespace glab::editor {

struct EditorContext {
    event::EventEmitter& event_emitter;
    platform::Window* window;
};

}  // namespace glab::editor
