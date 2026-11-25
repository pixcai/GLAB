#pragma once

#include "editor/editor_context.h"
#include "editor/editor_ui.h"

namespace glab::editor {

struct View3D : public EditorUI {
    View3D(EditorContext& context);
    ~View3D();

    void Render(EditorContext& context) override;
};

}  // namespace glab::editor
