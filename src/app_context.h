#pragma once

#include "core/event/event_emitter.h"
#include "editor/editor.h"
#include "platform/window.h"

namespace glab {

struct AppContext {
    event::EventEmitter event_emitter;
    platform::Window* window;
    editor::Editor* editor;
};

}  // namespace glab
