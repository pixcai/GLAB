#include "framebuffer.h"

GLAB_NAMESPACE_BEGIN()

Framebuffer::Framebuffer() : Framebuffer(1, 1) {}

Framebuffer::Framebuffer(int width, int height, int samples) : m_samples(samples) {
    createMSAAFBO();
    createResolveFBO();
    resize(width, height);
}

Framebuffer::~Framebuffer() { destroy(); }

Framebuffer::Framebuffer(Framebuffer&& other) noexcept {
    m_width = other.m_width;
    m_height = other.m_height;
    m_samples = other.m_samples;
    m_msaa_fbo = other.m_msaa_fbo;
    m_msaa_color = other.m_msaa_color;
    m_msaa_depth = other.m_msaa_depth;
    m_resolve_fbo = other.m_resolve_fbo;
    m_resolve_texture = other.m_resolve_texture;
    other.m_width = other.m_height = 0;
    other.m_msaa_fbo = other.m_msaa_color = other.m_msaa_depth = 0;
    other.m_resolve_fbo = other.m_resolve_texture = 0;
}

Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept {
    destroy();
    m_width = other.m_width;
    m_height = other.m_height;
    m_samples = other.m_samples;
    m_msaa_fbo = other.m_msaa_fbo;
    m_msaa_color = other.m_msaa_color;
    m_msaa_depth = other.m_msaa_depth;
    m_resolve_fbo = other.m_resolve_fbo;
    m_resolve_texture = other.m_resolve_texture;
    other.m_width = other.m_height = 0;
    other.m_msaa_fbo = other.m_msaa_color = other.m_msaa_depth = 0;
    other.m_resolve_fbo = other.m_resolve_texture = 0;
    return *this;
}

void Framebuffer::resize(int width, int height) {
    if (width == m_width && height == m_height) return;
    if (!(width > 0 && height > 0)) return;

    m_width = width;
    m_height = height;
    setSamples(m_samples);
}

void Framebuffer::setSamples(int samples) {
    m_samples = samples;
    glBindRenderbuffer(GL_RENDERBUFFER, m_msaa_color);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_samples, GL_RGBA8, m_width, m_height);

    glBindRenderbuffer(GL_RENDERBUFFER, m_msaa_depth);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_samples, GL_DEPTH24_STENCIL8, m_width,
                                     m_height);

    glBindTexture(GL_TEXTURE_2D, m_resolve_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Framebuffer::width() const noexcept { return m_width; }

int Framebuffer::height() const noexcept { return m_height; }

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_msaa_fbo);
    glViewport(0, 0, m_width, m_height);
}

void Framebuffer::unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void Framebuffer::resolve() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_msaa_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_resolve_fbo);

    glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT,
                      GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Framebuffer::texture() const noexcept { return m_resolve_texture; }

void Framebuffer::createMSAAFBO() {
    glGenFramebuffers(1, &m_msaa_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_msaa_fbo);

    glGenRenderbuffers(1, &m_msaa_color);
    glBindRenderbuffer(GL_RENDERBUFFER, m_msaa_color);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_msaa_color);

    glGenRenderbuffers(1, &m_msaa_depth);
    glBindRenderbuffer(GL_RENDERBUFFER, m_msaa_depth);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
                              m_msaa_depth);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::createResolveFBO() {
    glGenFramebuffers(1, &m_resolve_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_resolve_fbo);

    glGenTextures(1, &m_resolve_texture);
    glBindTexture(GL_TEXTURE_2D, m_resolve_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_resolve_texture,
                           0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::destroy() {
    if (m_msaa_fbo) {
        glDeleteFramebuffers(1, &m_msaa_fbo);
    }
    if (m_msaa_color) {
        glDeleteRenderbuffers(1, &m_msaa_color);
    }
    if (m_msaa_depth) {
        glDeleteRenderbuffers(1, &m_msaa_depth);
    }
    if (m_resolve_fbo) {
        glDeleteFramebuffers(1, &m_resolve_fbo);
    }
    if (m_resolve_texture) {
        glDeleteTextures(1, &m_resolve_texture);
    }
    m_width = m_height = 0;
    m_msaa_fbo = m_msaa_color = m_msaa_depth = 0;
    m_resolve_fbo = m_resolve_texture = 0;
}

GLAB_NAMESPACE_END()
