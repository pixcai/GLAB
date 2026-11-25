#pragma once

#include "editor/editor_context.h"
#include "editor/editor_ui.h"

namespace glab::editor {

struct Properties : public EditorUI {
    void Render(EditorContext& context) override;
};

}  // namespace glab::editor
