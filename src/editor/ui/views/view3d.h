#pragma once

#include "editor/editor_context.h"
#include "editor/ui/widget.h"

namespace glab::editor::ui {

struct View3D : public Widget {
    void Render(editor::EditorContext& editor_context) override;
};

}  // namespace glab::editor::ui
