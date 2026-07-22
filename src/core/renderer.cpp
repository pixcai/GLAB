#include "renderer.h"

#include "scene.h"

GLAB_NAMESPACE_BEGIN()

Renderer::Renderer(int width, int height) : m_width(width), m_height(height) {}

void Renderer::resize(int width, int height) noexcept {
    m_width = width;
    m_height = height;
}

void Renderer::beginFrame() {}

void Renderer::endFrame() {}

void Renderer::render(Scene& scene) {
    beginFrame();
    endFrame();
}

GLAB_NAMESPACE_END()
