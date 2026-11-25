#pragma once

#include "event_manager.h"

#include <GLFW/glfw3.h>

#include <memory>

namespace glab {

class EditorShell;

struct Engine final {
    Engine(const char* title, int width, int height);
    ~Engine();

    void Run();

private:
    GLFWwindow* m_window;
    EventManager m_event_manager;
    std::unique_ptr<EditorShell> m_editor_shell;
};

}  // namespace glab
