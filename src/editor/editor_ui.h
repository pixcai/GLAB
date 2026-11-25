#pragma once

#include "editor/editor_context.h"

namespace glab::editor {

struct EditorUI {
    EditorUI() = default;
    EditorUI(EditorContext& context) {}
    virtual ~EditorUI() = default;

    virtual void Render(EditorContext& context) = 0;

    bool visible{true};
};

}  // namespace glab::editor
