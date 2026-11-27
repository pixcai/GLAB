#include "buffer_object.h"
#include "rendering/vertex_layout.h"

#include <memory>
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

void BufferObject::Update(const void* data, GLintptr offset, GLsizeiptr size) {
    if (m_id == 0) {
        spdlog::error("Invalid GPU buffer");
        return;
    }
    Bind();
    glBufferSubData(m_target, offset, size, data);
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

RenderBufferObject::RenderBufferObject(const VertexLayout& layout)
    : vao(), vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW), ebo(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW) {
    vao.Bind();
    vbo.Bind();
    ebo.Bind();
    for (auto& attr : layout.attributes) {
        glEnableVertexAttribArray(attr.location);
        glVertexAttribPointer(attr.location, attr.size, attr.type, attr.normalized, layout.stride,
                              reinterpret_cast<void*>(attr.offset));
    }
    glBindVertexArray(0);
}

RenderBufferGroup::RenderBufferGroup(const VertexLayout& layout, GLsizei vbo_size, GLsizei ebo_size)
    : id(id_pool.Allocate())
    , m_vao()
    , m_vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW)
    , m_ebo(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW)
    , m_stride(layout.stride) {
    spdlog::debug("RenderBufferGroup(vbo={}, ebo={})", vbo_size, ebo_size);
    m_vao.Bind();
    m_vbo.Upload(nullptr, vbo_size);
    m_ebo.Upload(nullptr, ebo_size);
    for (auto& attr : layout.attributes) {
        glEnableVertexAttribArray(attr.location);
        glVertexAttribPointer(attr.location, attr.size, attr.type, attr.normalized, layout.stride,
                              reinterpret_cast<void*>(attr.offset));
    }
    glBindVertexArray(0);
    m_vbo_root = std::make_shared<Node>();
    m_ebo_root = std::make_shared<Node>();

    auto block_id = block_id_pool.Allocate();
    auto next = std::make_shared<Node>();
    next->id = block_id;
    next->count = vbo_size / m_stride;
    m_vbo_root->next = next;

    next = std::make_shared<Node>();
    next->id = block_id;
    next->count = ebo_size / sizeof(GLuint);
    m_ebo_root->next = next;
}

RenderBufferGroup::~RenderBufferGroup() {
    id_pool.Deallocate(id);
    spdlog::debug("~RenderBufferGroup()");
}

BufferBlock* RenderBufferGroup::Allocate(std::size_t vertex_count, std::size_t index_count) {
    BufferBlock block;
    block.group_id = id;

    auto& current = m_vbo_root->next;
    auto block_id = block_id_pool.Allocate();
    auto success = false;

    while (current) {
        if (current->is_free) {
            if (current->count >= vertex_count) {
                auto free_node = std::make_shared<Node>();
                free_node->id = block_id;
                free_node->count = current->count - vertex_count;
                free_node->offset = current->offset + vertex_count * m_stride;
                free_node->prev = current;
                free_node->next = current->next;
                current->next = free_node;

                current->count = vertex_count;
                current->is_free = false;
                block.id = current->id;
                block.vertex_count = vertex_count;
                block.vertex_offset = current->offset;
                block.basevertex = current->offset / m_stride;

                success = true;
                break;
            }
        }
        current = current->next;
    }
    if (!success) {
        block_id_pool.Deallocate(block_id);
        return nullptr;
    }
    current = m_ebo_root->next;
    success = false;
    while (current) {
        if (current->is_free) {
            if (current->count >= index_count) {
                auto free_node = std::make_shared<Node>();
                free_node->id = block_id;
                free_node->count = current->count - index_count;
                free_node->offset = current->offset + index_count * sizeof(GLuint);
                free_node->prev = current;
                free_node->next = current->next;
                current->next = free_node;

                current->count = index_count;
                current->is_free = false;
                block.id = current->id;
                block.index_count = index_count;
                block.index_offset = current->offset;

                success = true;
                break;
            }
        }
        current = current->next;
    }
    if (!success) {
        block_id_pool.Deallocate(block_id);
        return nullptr;
    }
    m_blocks.Insert(block_id, block);
    return m_blocks.Get(block_id);
}

void RenderBufferGroup::Deallocate(BufferBlockID id) {
    if (auto block = m_blocks.Get(id); block != nullptr) {
        m_free_blocks.emplace(id, true);
    }
}

void RenderBufferGroup::Upload(BufferBlockID id, const void* vertices, std::size_t vertex_count, const void* indices,
                               std::size_t index_count) {
    if (auto block = m_blocks.Get(id); block != nullptr) {
        if (block->vertex_count < vertex_count || block->index_count < index_count) {
            return;
        }
        m_vbo.Update(vertices, block->vertex_offset, vertex_count * m_stride);
        m_ebo.Update(indices, block->index_offset, index_count * sizeof(GLuint));
    }
}

}  // namespace glab::rendering
