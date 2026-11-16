#include "app.h"
#include "config/config.h"
#include "editor/editor.h"
#include "platform/platform.h"
#include "platform/window.h"

#include <cstdlib>
#include <exception>
#include <memory>

#include <spdlog/spdlog.h>

namespace glab {

void App::Init() {
    spdlog::set_level(config::kLogLevel);

    platform::Init();

    auto& event_emitter = m_context.event_emitter;

    m_window = std::make_unique<platform::Window>("GLAB", config::kWindowSize.x, config::kWindowSize.y, event_emitter);

    auto window = m_window.get();

    editor::Init(window);

    m_editor = std::make_unique<editor::Editor>(window, event_emitter);

    m_context.window = window;
    m_context.editor = m_editor.get();
}

void App::Shutdown() {
    m_context = {};
    m_editor.reset();
    m_window.reset();

    editor::Shutdown();
    platform::Shutdown();
}

int App::Run() {
    int result = EXIT_SUCCESS;

    try {
        Init();

        while (!m_window->ShouldClose()) {
            m_window->PollEvents();
            m_editor->BeginFrame();
            m_editor->Render();
            m_editor->EndFrame();
            m_window->SwapBuffers();
        }
    } catch (const std::exception& e) {
        spdlog::critical(e.what());
        result = EXIT_FAILURE;
    }

    Shutdown();
    spdlog::info("Exit({})", result);

    return result;
}

}  // namespace glab
