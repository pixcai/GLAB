#pragma once

#include <string>

#include "common.h"

GLAB_NAMESPACE_BEGIN()

struct DisplayName : IComponent {
    std::string text;
};

struct Relationship : IComponent {
    Entity parent;
    Entity first_child;
    Entity prev_sibling;
    Entity next_sibling;
    std::uint32_t child_count{0};
};

GLAB_NAMESPACE_END()
