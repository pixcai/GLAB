#include "gpu_datatype.h"

#include <utility>

#include <glad/gl.h>
#include <spdlog/spdlog.h>

namespace glab::rendering {

GPUBuffer::GPUBuffer(GLenum target, GLenum usage) : m_target(target), m_usage(usage) { glGenBuffers(1, &m_id); }

GPUBuffer::~GPUBuffer() {
    if (m_id != 0) {
        glDeleteBuffers(1, &m_id);
        m_id = 0;
    }
}

GPUBuffer::GPUBuffer(GPUBuffer&& other) noexcept : m_target(other.m_target), m_id(std::exchange(other.m_id, 0)) {}

GPUBuffer& GPUBuffer::operator=(GPUBuffer&& other) noexcept {
    if (&other != this) {
        m_target = other.m_target;
        if (m_id != 0) {
            glDeleteBuffers(1, &m_id);
        }
        m_id = std::exchange(other.m_id, 0);
    }
    return *this;
}

void GPUBuffer::Bind() const {
    if (m_id == 0) {
        spdlog::error("Invalid GPU buffer");
        return;
    }
    glBindBuffer(m_target, m_id);
}

void GPUBuffer::Upload(const void* data, GLsizeiptr size) {
    if (m_id == 0) {
        spdlog::error("Invalid GPU buffer");
        return;
    }
    Bind();
    glBufferData(m_target, size, data, m_usage);
}

GPUVertexArray::GPUVertexArray(GPUVertexLayout layout) : m_layout(std::move(layout)) { glGenVertexArrays(1, &m_id); }

GPUVertexArray::~GPUVertexArray() {
    if (m_id != 0) {
        glDeleteVertexArrays(1, &m_id);
        m_id = 0;
    }
}

GPUVertexArray::GPUVertexArray(GPUVertexArray&& other) noexcept
    : m_layout(std::move(other.m_layout)), m_id(std::exchange(other.m_id, 0)) {}

GPUVertexArray& GPUVertexArray::operator=(GPUVertexArray&& other) noexcept {
    if (&other != this) {
        m_layout = std::move(other.m_layout);
        if (m_id != 0) {
            glDeleteVertexArrays(1, &m_id);
        }
        m_id = std::exchange(other.m_id, 0);
    }
    return *this;
}

void GPUVertexArray::Bind() const {
    if (m_id == 0) {
        spdlog::error("Invalid GPU vertex array");
    }
    glBindVertexArray(m_id);
}

void GPUVertexArray::SetVertexBuffer(const GPUBuffer& buffer) {
    Bind();
    buffer.Bind();

    for (const auto& attr : m_layout.attributes) {
        glEnableVertexAttribArray(attr.location);
        glVertexAttribPointer(attr.location, attr.size, attr.type, attr.normalized, attr.stride,
                              reinterpret_cast<void*>(attr.offset));
    }
}

void GPUVertexArray::SetBuffer(const GPUBuffer& buffer) {
    Bind();
    buffer.Bind();
}

}  // namespace glab::rendering
