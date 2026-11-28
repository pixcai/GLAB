#pragma once

#include "texture.h"

#include <utility>

#include <glad/gl.h>

namespace glab::rendering {

class Framebuffer {
public:
    Framebuffer(GLsizei width, GLsizei height);
    ~Framebuffer();

    Framebuffer(const Framebuffer& other) = delete;
    Framebuffer& operator=(const Framebuffer& other) = delete;

    Framebuffer(Framebuffer&& other) noexcept;
    Framebuffer& operator=(Framebuffer&& other) noexcept;

    void Bind() const;
    void Unbind() const;

    void Resize(GLsizei width, GLsizei height);

    std::pair<GLsizei, GLsizei> GetSize() const { return {m_width, m_height}; };

public:
    Texture color_texture, depth_texture;

private:
    GLsizei m_width{0}, m_height{0};
    GLuint m_id{0};
};

}  // namespace glab::rendering
