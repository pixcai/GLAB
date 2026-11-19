#pragma once

#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace glab::geometry {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};

}  // namespace glab::geometry
