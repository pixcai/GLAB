#include "mesh/vertex.h"
#include "render_queue.h"
#include "renderer.h"
#include "rendering/vertex_layout.h"
#include "resource_manager.h"
#include "scene/camera.h"

#include <glad/gl.h>
#include <spdlog/spdlog.h>

namespace glab::rendering {

MeshRenderer::MeshRenderer(RenderContext& context)
    : m_context(context), m_buffer_group(mesh::default_layout, 4 * 1024 * 1024, 1024 * 1024) {}

void MeshRenderer::BeginFrame() { m_buffer_group.Bind(); }

void MeshRenderer::Render(const RenderTask& task, const scene::Camera& camera) {
    auto material = resource_manager.TryGet(task.material_id);
    if (!material) {
        return;
    }
    auto shader = m_context.shader_manager->Get("mesh");
    if (!shader) {
        return;
    }
    shader->Use();
    shader->SetUniform("view_matrix", camera.view_matrix);
    shader->SetUniform("projection_matrix", camera.projection_matrix);
    shader->SetUniform("color", material->base_color);

    for (auto& item : task.items) {
        shader->SetUniform("model_matrix", item.world_matrix);
        DrawItem(item, camera);
    }
}

void MeshRenderer::DrawItem(const RenderItem& item, const scene::Camera& camera) {
    auto mesh = resource_manager.TryGet(item.mesh_id);
    if (!mesh) {
        return;
    }

    auto block = mesh->block;

    if (mesh->is_dirty && mesh->layout_type == VertexLayoutType::kDefault) {
        if (!block) {
            block = mesh->block = m_buffer_group.Allocate(mesh->vertices.size(), mesh->indices.size());
        }
        spdlog::debug("Prepare upload: {}", glGetError());
        m_buffer_group.Upload(block->id, mesh->vertices.data(), mesh->vertices.size(), mesh->indices.data(),
                              mesh->indices.size());
        mesh->is_dirty = false;
        spdlog::debug("Upload Mesh(index={}, generation={})", item.mesh_id.index, item.mesh_id.generation);
    }
    glDrawElementsBaseVertex(GL_TRIANGLES, block->index_count, GL_UNSIGNED_INT,
                             reinterpret_cast<void*>(block->index_offset), block->basevertex);
}

void MeshRenderer::EndFrame() {}

}  // namespace glab::rendering
