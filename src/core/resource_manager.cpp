#include "resource_manager.h"

#include "mesh.h"
#include "shader.h"

GLAB_NAMESPACE_BEGIN()

ResourceManager& ResourceManager::get() noexcept {
    static ResourceManager singleton;
    return singleton;
}

ResourceManager::~ResourceManager() {
    for (auto& [_, handle] : m_mesh_map) {
        m_destroy_queue.push(handle.get());
    }
    for (auto& [_, handle] : m_shader_map) {
        m_destroy_queue.push(handle.get());
    }
    flushDestroyQueue();
}

void ResourceManager::pushDestroyQueue(IResource* resource) {
    if (resource) {
        std::lock_guard lock{m_mutex};
        m_destroy_queue.push(resource);
    } else {
        LOG_WARN("Cannot add a nullptr pointer to the destroy queue");
    }
}

void ResourceManager::flushDestroyQueue() {
    std::lock_guard lock{m_mutex};

    while (!m_destroy_queue.empty()) {
        auto resource = m_destroy_queue.front();
        auto path = resource->resource_path;

        m_destroy_queue.pop();
        resource->destroy();

        // If the path is empty, the resource is built-in and is not tracked in the resource map
        // Otherwise, the resource was loaded from a file and should be erased from the map
        if (!path.empty()) {
            switch (resource->resource_type) {
                case ResourceType::Mesh:
                    m_mesh_map.erase(path);
                    break;
                case ResourceType::Shader:
                    m_shader_map.erase(path);
                    break;
                default:
                    break;
            }
        }
        // Resources are allocated using new and must be released with delete
        delete resource;
    }
}

void ResourceManager::loadMesh(std::string_view path,
                               std::function<void(ResourceHandle<Mesh>)> callback) {}

void ResourceManager::loadShader(std::string_view path,
                                 std::function<void(ResourceHandle<Shader>)> callback) {}

void Mesh::destroy() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    vao = vbo = ebo = 0;
    vertices.clear();
    indices.clear();
}

void Shader::destroy() {
    glDeleteProgram(program);
    program = 0;
    uniform_map.clear();
}

GLAB_NAMESPACE_END()
