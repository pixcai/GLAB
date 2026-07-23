#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "../gl.h"
#include "resource.h"

GLAB_NAMESPACE_BEGIN()

struct Vertex {
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 normal{0.0f, 0.0f, 0.0f};
    glm::vec2 uv{0.0f, 0.0f};
};

struct Mesh : IResource {
    GLuint vao{0}, vbo{0}, ebo{0};

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    Mesh() : IResource(ResourceType::Mesh) {}

    void destroy() override;
};

struct MeshRenderer : IComponent {
    ResourceHandle<Mesh> mesh_handle{};
};

GLAB_NAMESPACE_END()
