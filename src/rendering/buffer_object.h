#pragma once

#include "core/flat_hash_map.h"
#include "core/id.h"
#include "vertex_layout.h"

#include <memory>
#include <unordered_map>

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
    void Update(const void* data, GLintptr offset, GLsizeiptr size);

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

struct RenderBufferObject {
    RenderBufferObject(const VertexLayout& layout);
    ~RenderBufferObject() = default;

    VertexArrayObject vao;
    BufferObject vbo, ebo;
};

struct BufferBlock;
struct RenderBufferGroup;

using BufferBlockID = core::ID<BufferBlock>;
using RenderBufferGroupID = core::ID<RenderBufferGroup>;

struct BufferBlock {
    RenderBufferGroupID group_id;
    BufferBlockID id;
    GLsizeiptr vertex_count{0}, index_count{0};
    GLintptr vertex_offset{0}, index_offset{0};
    GLint basevertex{0};
};

struct RenderBufferGroup {
    inline static core::IDPool<RenderBufferGroup> id_pool;
    inline static core::IDPool<BufferBlock> block_id_pool;

    RenderBufferGroupID id;

    struct Node {
        BufferBlockID id;
        bool is_free{true};
        GLuint count{0}, offset{0};
        std::weak_ptr<Node> prev;
        std::shared_ptr<Node> next;
    };

    RenderBufferGroup(const VertexLayout& layout, GLsizei vbo_size, GLsizei ebo_size);
    ~RenderBufferGroup();

    void Bind() const { m_vao.Bind(); }

    BufferBlock* Allocate(std::size_t vertex_count, std::size_t index_count);
    void Deallocate(BufferBlockID id);

    void Upload(BufferBlockID id, const void* vertices, std::size_t vertex_count, const void* indices,
                std::size_t index_count);

private:
    VertexArrayObject m_vao;
    BufferObject m_vbo, m_ebo;
    GLsizei m_stride;
    std::shared_ptr<Node> m_vbo_root;
    std::shared_ptr<Node> m_ebo_root;
    core::FlatHashMap<BufferBlockID, BufferBlock> m_blocks;
    std::unordered_map<BufferBlockID, bool> m_free_blocks;
};

}  // namespace glab::rendering
