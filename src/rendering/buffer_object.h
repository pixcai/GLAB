#pragma once

#include <glad/gl.h>

namespace glab::rendering {

struct BufferObject {
    BufferObject(GLenum target, GLenum usage);
    ~BufferObject();

    BufferObject(const BufferObject& other) = delete;
    BufferObject& operator=(const BufferObject& other) = delete;

    BufferObject(BufferObject&& other) noexcept;
    BufferObject& operator=(BufferObject&& other) noexcept;

    void Bind() const;

    void Upload(const void* data, GLsizeiptr size);

private:
    GLenum m_target, m_usage;
    GLuint m_id;
};

struct VertexArrayObject {
    VertexArrayObject();
    ~VertexArrayObject();

    VertexArrayObject(const VertexArrayObject& other) = delete;
    VertexArrayObject& operator=(const VertexArrayObject& other) = delete;

    VertexArrayObject(VertexArrayObject&& other) noexcept;
    VertexArrayObject& operator=(VertexArrayObject&& other) noexcept;

    void Bind() const;

private:
    GLuint m_id;
};

}  // namespace glab::rendering
