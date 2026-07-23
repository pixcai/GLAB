#pragma once

#include "../gl.h"
#include "../namespace.h"

GLAB_NAMESPACE_BEGIN()

class Framebuffer {
public:
    Framebuffer();
    Framebuffer(int width, int height, int samples = 4);
    ~Framebuffer();

    Framebuffer(const Framebuffer& other) = delete;
    Framebuffer& operator=(const Framebuffer& other) = delete;

    Framebuffer(Framebuffer&& other) noexcept;
    Framebuffer& operator=(Framebuffer&& other) noexcept;

    void resize(int width, int height);
    void setSamples(int samples);

    int width() const noexcept;
    int height() const noexcept;

    void bind();
    void unbind();

    void resolve();
    GLuint texture() const noexcept;

private:
    void createMSAAFBO();
    void createResolveFBO();
    void destroy();

private:
    int m_width{0}, m_height{0};
    int m_samples;

    GLuint m_msaa_fbo{0};
    GLuint m_msaa_color{0};
    GLuint m_msaa_depth{0};

    GLuint m_resolve_fbo{0};
    GLuint m_resolve_texture{0};
};

GLAB_NAMESPACE_END()
