#include "framebuffer.h"

#include <utility>

#include <glad/gl.h>
#include <spdlog/spdlog.h>

namespace glab::rendering {

Framebuffer::Framebuffer(GLsizei width, GLsizei height)
    : m_width(width)
    , m_height(height)
    , color_texture(width, height)
    , depth_texture(GL_TEXTURE_2D, Texture::Format::Depth24, width, height) {
    glGenFramebuffers(1, &m_id);
    Bind();
    spdlog::debug("Bind color attachment, GL={}", glGetError());
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, color_texture.GetTarget(), color_texture.GetID(), 0);
    spdlog::debug("Bind depth attachment, GL={}", glGetError());
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_texture.GetTarget(), depth_texture.GetID(), 0);
    Unbind();
}

Framebuffer::~Framebuffer() {
    if (m_id != 0) {
        glDeleteFramebuffers(1, &m_id);
        m_id = 0;
    }
}

Framebuffer::Framebuffer(Framebuffer&& other) noexcept
    : m_id(std::exchange(other.m_id, 0))
    , m_width(std::exchange(other.m_width, 0))
    , m_height(std::exchange(other.m_height, 0))
    , color_texture(std::move(other.color_texture))
    , depth_texture(std::move(other.depth_texture)) {}

Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept {
    if (this != &other) {
        if (m_id != 0) {
            glDeleteFramebuffers(1, &m_id);
        }
        m_id = std::exchange(other.m_id, 0);
        m_width = std::exchange(other.m_width, 0);
        m_height = std::exchange(other.m_height, 0);
        color_texture = std::move(other.color_texture);
        depth_texture = std::move(other.depth_texture);
    }
    return *this;
}

void Framebuffer::Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_id); }

void Framebuffer::Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void Framebuffer::Resize(GLsizei width, GLsizei height) {
    if (width == m_width && height == m_height) {
        return;
    }
    color_texture.Resize(width, height);
    depth_texture.Resize(width, height);
    m_width = width;
    m_height = height;
}

}  // namespace glab::rendering
