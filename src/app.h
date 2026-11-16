#pragma once

#include "app_context.h"
#include "editor/editor.h"
#include "platform/window.h"

#include <memory>

namespace glab {

class App {
public:
    int Run();

private:
    void Init();
    void Shutdown();

private:
    AppContext m_context{};
    std::unique_ptr<platform::Window> m_window;
    std::unique_ptr<editor::Editor> m_editor;
};

}  // namespace glab
