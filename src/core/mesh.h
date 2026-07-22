#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "../gl.h"
#include "resource.h"

GLAB_NAMESPACE_BEGIN()

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

struct Mesh : Resource {
    GLuint vao{0}, vbo{0}, ebo{0};

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    void destroy() override;
};

struct MeshComponent : Component {
    ResourceHandle<Mesh> mesh_handle;
};

GLAB_NAMESPACE_END()
