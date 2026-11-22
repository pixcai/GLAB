#pragma once

#include "gpu_datatype.h"
#include "mesh/mesh.h"

#include <glad/gl.h>

namespace glab::rendering {

struct GPUMesh {
    GPUMesh(GPUVertexLayout layout);
    ~GPUMesh() = default;

    GPUMesh(const GPUMesh& other) = delete;
    GPUMesh& operator=(const GPUMesh& other) = delete;

    GPUMesh(GPUMesh&& other) noexcept;
    GPUMesh& operator=(GPUMesh&& other) noexcept;

    void Bind() const;

    GLuint GetIndexCount() { return m_vertex_count; }
    GLuint GetVertexCount() { return m_index_count; }

    void Upload(const mesh::Mesh& mesh);

private:
    GPUVertexArray m_vao;
    GPUBuffer m_vbo{GL_ARRAY_BUFFER, GL_STATIC_DRAW}, m_ebo{GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW};

    GLuint m_vertex_count{0}, m_index_count{0};
};

}  // namespace glab::rendering
