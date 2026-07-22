#pragma once

#include <unordered_map>

#include "../gl.h"
#include "resource.h"

GLAB_NAMESPACE_BEGIN()

struct Shader : Resource {
    GLuint program{0};
    std::unordered_map<std::string, GLint> uniform_map;

    Shader() : Resource(ResourceType::Shader) {}

    void destroy() override;
};

GLAB_NAMESPACE_END()
