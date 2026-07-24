#include "resource_manager.h"

#include "mesh.h"
#include "shader.h"

GLAB_NAMESPACE_BEGIN()

ResourceManager& ResourceManager::get() {
    static ResourceManager singleton;
    return singleton;
}

ResourceManager::~ResourceManager() {
    m_handle_map.clear();
    flushDestroyQueue();
}

void ResourceManager::pushDestroyQueue(IResource* resource) {
    if (resource) {
        m_destroy_queue.push(resource);
    } else {
        LOG_WARN("Cannot add a nullptr pointer to the destroy queue");
    }
}

void ResourceManager::flushDestroyQueue() {
    while (!m_destroy_queue.empty()) {
        auto resource = m_destroy_queue.front();

        m_destroy_queue.pop();
        resource->destroy();

        // Resources are allocated using new and must be released with delete
        delete resource;
    }
}

template <ResourceLike Resource>
ResourceHandle<Resource> ResourceManager::load(const std::string& path) {
    LOG_WARN("Attempting to load an unsupported resource: {}", path);
}

template <>
ResourceHandle<Mesh> ResourceManager::load(const std::string& path) {
    return {};
}

template <>
ResourceHandle<Shader> ResourceManager::load(const std::string& path) {
    return {};
}

void Mesh::destroy() {
    if (vao) {
        glDeleteVertexArrays(1, &vao);
    }
    if (vbo) {
        glDeleteBuffers(1, &vbo);
    }
    if (ebo) {
        glDeleteBuffers(1, &ebo);
    }
    vao = vbo = ebo = 0;
    vertices.clear();
    indices.clear();
    LOG_DEBUG("Mesh (id={}, name={}) destroyed", id, name);
}

void Shader::destroy() {
    if (program) {
        glDeleteProgram(program);
    }
    program = 0;
    uniform_map.clear();
    LOG_DEBUG("Shader (id={}, name={}) destroyed", id, name);
}

GLAB_NAMESPACE_END()
