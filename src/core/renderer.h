#pragma once

#include "common.h"

GLAB_NAMESPACE_BEGIN()

class Renderer {
public:
    Renderer() = default;
    Renderer(int width, int height);

    void resize(int width, int height) noexcept;

    void beginFrame();
    void endFrame();
    void render(Scene& scene);

private:
    int m_width{0}, m_height{0};
};

GLAB_NAMESPACE_END()
