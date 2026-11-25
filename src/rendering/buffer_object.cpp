#include "buffer_object.h"

#include <utility>

#include <glad/gl.h>
#include <spdlog/spdlog.h>

namespace glab::rendering {

BufferObject::BufferObject(GLenum target, GLenum usage) : m_target(target), m_usage(usage) { glGenBuffers(1, &m_id); }

BufferObject::~BufferObject() {
    if (m_id != 0) {
        glDeleteBuffers(1, &m_id);
        m_id = 0;
    }
}

BufferObject::BufferObject(BufferObject&& other) noexcept
    : m_target(other.m_target), m_id(std::exchange(other.m_id, 0)) {}

BufferObject& BufferObject::operator=(BufferObject&& other) noexcept {
    if (&other != this) {
        m_target = other.m_target;
        if (m_id != 0) {
            glDeleteBuffers(1, &m_id);
        }
        m_id = std::exchange(other.m_id, 0);
    }
    return *this;
}

void BufferObject::Bind() const {
    if (m_id == 0) {
        spdlog::error("Invalid GPU buffer");
        return;
    }
    glBindBuffer(m_target, m_id);
}

void BufferObject::Upload(const void* data, GLsizeiptr size) {
    if (m_id == 0) {
        spdlog::error("Invalid GPU buffer");
        return;
    }
    Bind();
    glBufferData(m_target, size, data, m_usage);
}

VertexArrayObject::VertexArrayObject() { glGenVertexArrays(1, &m_id); }

VertexArrayObject::~VertexArrayObject() {
    if (m_id != 0) {
        glDeleteVertexArrays(1, &m_id);
        m_id = 0;
    }
}

VertexArrayObject::VertexArrayObject(VertexArrayObject&& other) noexcept : m_id(std::exchange(other.m_id, 0)) {}

VertexArrayObject& VertexArrayObject::operator=(VertexArrayObject&& other) noexcept {
    if (&other != this) {
        if (m_id != 0) {
            glDeleteVertexArrays(1, &m_id);
        }
        m_id = std::exchange(other.m_id, 0);
    }
    return *this;
}

void VertexArrayObject::Bind() const {
    if (m_id == 0) {
        spdlog::error("Invalid GPU vertex array");
    }
    glBindVertexArray(m_id);
}

}  // namespace glab::rendering
