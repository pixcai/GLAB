#pragma once

#include "core/event_manager.h"

namespace glab {

struct Global {
    inline static core::EventManager event_manager;
};

}  // namespace glab
