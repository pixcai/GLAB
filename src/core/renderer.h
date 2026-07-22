#pragma once

#include <vector>

#include "common.h"
#include "rendering.h"

GLAB_NAMESPACE_BEGIN()

class Renderer {
public:
    Renderer() = default;
    Renderer(int width, int height);

    void resize(int width, int height) noexcept;

    void render(const std::vector<RenderItem>& render_items);

private:
    void beginFrame();
    void endFrame();
    void buildCommandQueue(const std::vector<RenderItem>& render_items);
    void sortOpaque();
    void sortTransparent();
    DrawCommand createCommand(const RenderItem& render_item);
    void executeCommands(const std::vector<DrawCommand>& commands);

private:
    int m_width{0}, m_height{0};
    std::vector<DrawCommand> m_opaque_queue;
    std::vector<DrawCommand> m_transparent_queue;
};

GLAB_NAMESPACE_END()
