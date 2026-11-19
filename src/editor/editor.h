#pragma once

#include "editor/ui/widget.h"
#include "editor_context.h"
#include "platform/window.h"

#include <memory>
#include <vector>

namespace glab::editor {

void Init(platform::Window* window);
void Shutdown();

class Editor {
public:
    Editor();
    ~Editor();

    void BeginFrame();
    void Render();
    void EndFrame();

private:
    EditorContext m_context;
    std::vector<std::unique_ptr<ui::Widget>> m_widgets;
};

}  // namespace glab::editor
