#include "renderer.h"

#include "../logger.h"

GLAB_NAMESPACE_BEGIN()

Renderer::Renderer(int width, int height) : m_width(width), m_height(height) {}

void Renderer::resize(int width, int height) noexcept {
    m_width = width;
    m_height = height;
}

void Renderer::beginFrame() {}

void Renderer::endFrame() {}

void Renderer::render(const std::vector<RenderItem>& render_items) {
    buildCommandQueue(render_items);
    beginFrame();
    executeCommands(m_opaque_queue);
    executeCommands(m_transparent_queue);
    endFrame();
}

void Renderer::buildCommandQueue(const std::vector<RenderItem>& render_items) {
    m_opaque_queue.clear();
    m_transparent_queue.clear();

    for (auto& render_item : render_items) {
        if (render_item.render_queue < 2500) {
            m_opaque_queue.push_back(createCommand(render_item));
        } else {
            m_transparent_queue.push_back(createCommand(render_item));
        }
    }

    sortOpaque();
    sortTransparent();
}

void Renderer::sortOpaque() {}

void Renderer::sortTransparent() {}

DrawCommand Renderer::createCommand(const RenderItem& render_item) {
    DrawCommand command{};
    command.render_queue = render_item.render_queue;
    command.world_matrix = render_item.world_matrix;
    command.mesh_handle = render_item.mesh_handle;
    return command;
}

void Renderer::executeCommands(const std::vector<DrawCommand>& commands) {
    LOG_DEBUG("command count = {}", commands.size());
}

GLAB_NAMESPACE_END()
