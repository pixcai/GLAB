#pragma once

#include "editor/editor_context.h"
#include "widget.h"

namespace glab::editor::ui {

struct MainMenuBar : public Widget {
    void Render(editor::EditorContext& editor_context) override;
};

}  // namespace glab::editor::ui
