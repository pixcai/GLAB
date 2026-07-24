#pragma once

#include "core/common.h"

GLAB_NAMESPACE_BEGIN()

struct EditorContext {
    static EditorContext& instance() noexcept;

    Scene* scene{nullptr};
    Renderer* renderer{nullptr};
};

GLAB_NAMESPACE_END()
