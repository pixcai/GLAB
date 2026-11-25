#pragma once

#include "editor/editor_context.h"
#include "editor/editor_ui.h"

namespace glab::editor {

struct Outliner : public EditorUI {
    void Render(EditorContext& context) override;
};

}  // namespace glab::editor
