#include "geometry/mesh.h"
#include "gpu_datatype.h"
#include "gpu_mesh.h"

#include <utility>

#include <glad/gl.h>

namespace glab::rendering {

GPUMesh::GPUMesh(GPUVertexLayout layout) : m_vao(std::move(layout)) {}

GPUMesh::GPUMesh(GPUMesh&& other) noexcept
    : m_vao(std::move(other.m_vao))
    , m_vbo(std::move(other.m_vbo))
    , m_ebo(std::move(other.m_ebo))
    , m_vertex_count(std::exchange(other.m_vertex_count, 0))
    , m_index_count(std::exchange(other.m_index_count, 0)) {}

GPUMesh& GPUMesh::operator=(GPUMesh&& other) noexcept {
    if (&other != this) {
        m_vao = std::move(other.m_vao);
        m_vbo = std::move(other.m_vbo);
        m_ebo = std::move(other.m_ebo);
        m_vertex_count = std::exchange(other.m_vertex_count, 0);
        m_index_count = std::exchange(other.m_index_count, 0);
    }
    return *this;
}

void GPUMesh::Bind() const { m_vao.Bind(); }

void GPUMesh::Upload(const geometry::Mesh& mesh) {
    Bind();
    m_vbo.Upload(mesh.vertices.data(), mesh.vertices.size() * sizeof(geometry::Vertex));
    if (!mesh.indices.empty()) {
        m_ebo.Upload(mesh.indices.data(), mesh.indices.size() * sizeof(GLuint));
    }
}

}  // namespace glab::rendering
