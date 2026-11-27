#pragma once

#include "rendering/vertex_layout.h"

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace glab::mesh {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

inline rendering::VertexLayout default_layout{rendering::VertexLayoutType::kDefault,
                                              sizeof(Vertex),
                                              {{0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position)},
                                               {1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal)},
                                               {2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uv)}}};

}  // namespace glab::mesh
