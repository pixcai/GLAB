#pragma once

namespace glab::platform {

struct FramebufferResizeEvent {
    int width, height;
};

struct KeyPressedEvent {
    int key, code, action, mods;
};

struct MousePressedEvent {
    int button, action, mods;
};

struct MouseMoveEvent {
    double dx, dy;
};

struct MouseWheelEvent {
    double dx, dy;
};

}  // namespace glab::platform
