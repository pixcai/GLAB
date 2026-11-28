#pragma once

#include <glad/gl.h>

namespace glab::rendering {

class Texture {
public:
    enum class Format {
        RGBA8,
        Depth24,
    };

    Texture(GLsizei width, GLsizei height) : Texture(GL_TEXTURE_2D, Format::RGBA8, width, height) {}
    Texture(GLenum target, Format format, GLsizei width, GLsizei height);
    ~Texture();

    Texture(const Texture& other) = delete;
    Texture& operator=(const Texture& other) = delete;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    GLuint GetID() const { return m_id; }
    GLenum GetTarget() const { return m_target; }

    void Resize(GLsizei width, GLsizei height);

private:
    GLenum m_target;
    Format m_format;
    GLsizei m_width{0}, m_height{0};
    GLuint m_id{0};
};

}  // namespace glab::rendering
