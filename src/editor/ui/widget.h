#pragma once

#include "editor/editor_context.h"

namespace glab::editor::ui {

struct Widget {
    Widget() = default;
    virtual ~Widget() = default;

    virtual void Render(editor::EditorContext& editor_context) = 0;

    bool visible{true};
};

}  // namespace glab::editor::ui
