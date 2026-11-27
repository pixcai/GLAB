#pragma once

#include <vector>

#include <glad/gl.h>

namespace glab::rendering {

struct VertexAttribute {
    GLuint location;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizeiptr offset;
};

enum class VertexLayoutType : std::uint8_t {
    kDefault,
};

struct VertexLayout {
    VertexLayoutType type;
    GLsizei stride;
    std::vector<VertexAttribute> attributes;
};

}  // namespace glab::rendering
