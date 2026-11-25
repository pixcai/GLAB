#pragma once

#include "editor/editor.h"
#include "event_manager.h"

namespace glab {

class EditorShell {
public:
    EditorShell(EventManager* event_manager);
    ~EditorShell();

    void BeginFrame();
    void Render();
    void EndFrame();

private:
    void RenderMainMenuBar();
    void RenderStatusBar();
    void RenderDockSpace();

    EventManager* m_event_manager;
    editor::Editor m_editor;
};

}  // namespace glab
