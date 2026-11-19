#pragma once

#include <vector>

#include <glad/gl.h>

namespace glab::rendering {

struct GPUVertexAttribute {
    GLuint location;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    std::size_t offset;
};

struct GPUVertexLayout {
    std::vector<GPUVertexAttribute> attributes;

    GPUVertexLayout(GLsizei stride) : m_stride(stride) {}

    void AddFloat(GLuint location, GLint size, std::size_t offset) { AddFloat(location, size, offset, GL_FALSE); }

    void AddFloat(GLuint location, GLint size, std::size_t offset, GLboolean normalized) {
        attributes.emplace_back(location, size, GL_FLOAT, normalized, m_stride, offset);
    }

private:
    GLsizei m_stride;
};

struct GPUBuffer {
    GPUBuffer(GLenum target);
    ~GPUBuffer();

    GPUBuffer(const GPUBuffer& other) = delete;
    GPUBuffer& operator=(const GPUBuffer& other) = delete;

    GPUBuffer(GPUBuffer&& other) noexcept;
    GPUBuffer& operator=(GPUBuffer&& other) noexcept;

    void Bind() const;
    void Unbind() const;

    void SetData(const void* data, GLsizeiptr size, GLenum usage);

private:
    GLenum m_target;
    GLuint m_id;
};

struct GPUVertexArray {
    GPUVertexArray(GPUVertexLayout layout);
    ~GPUVertexArray();

    GPUVertexArray(const GPUVertexArray& other) = delete;
    GPUVertexArray& operator=(const GPUVertexArray& other) = delete;

    GPUVertexArray(GPUVertexArray&& other) noexcept;
    GPUVertexArray& operator=(GPUVertexArray&& other) noexcept;

    void Bind() const;
    void Unbind() const;

    void SetVertexBuffer(const GPUBuffer& buffer);
    void SetBuffer(const GPUBuffer& buffer);

private:
    GPUVertexLayout m_layout;
    GLuint m_id;
};

}  // namespace glab::rendering
