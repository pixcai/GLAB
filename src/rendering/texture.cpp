#include "texture.h"

#include <utility>

#include <glad/gl.h>
#include <spdlog/spdlog.h>

namespace glab::rendering {

Texture::Texture(GLenum target, Format format, GLsizei width, GLsizei height) : m_target(target), m_format(format) {
    spdlog::debug("Texture(width={}, height={})", width, height);
    glGenTextures(1, &m_id);
    Resize(width, height);
}

Texture::~Texture() {
    if (m_id != 0) {
        spdlog::debug("~Texture()");
        glDeleteTextures(1, &m_id);
        m_id = 0;
    }
}

Texture::Texture(Texture&& other) noexcept
    : m_target(other.m_target)
    , m_format(other.m_format)
    , m_width(other.m_width)
    , m_height(other.m_height)
    , m_id(std::exchange(other.m_id, 0)) {}

Texture& Texture::operator=(Texture&& other) noexcept {
    if (this != &other) {
        m_target = other.m_target;
        m_format = other.m_format;
        m_width = other.m_width;
        m_height = other.m_height;
        m_id = std::exchange(other.m_id, 0);
    }
    return *this;
}

void Texture::Resize(GLsizei width, GLsizei height) {
    if (width == m_width && height == m_height) {
        return;
    }
    m_width = width;
    m_height = height;

    GLint internal_format;
    GLenum format, type;

    switch (m_format) {
        case Format::RGBA8:
            internal_format = GL_RGBA8;
            format = GL_RGBA;
            type = GL_UNSIGNED_BYTE;
            break;
        case Format::Depth24:
            internal_format = GL_DEPTH_COMPONENT24;
            format = GL_DEPTH_COMPONENT;
            type = GL_UNSIGNED_INT;
            break;
    }
    glBindTexture(m_target, m_id);

    glTexImage2D(m_target, 0, internal_format, m_width, m_height, 0, format, type, nullptr);

    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(m_target, 0);
}

}  // namespace glab::rendering
