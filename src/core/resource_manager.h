#pragma once

#include <functional>
#include <mutex>
#include <queue>
#include <string>
#include <string_view>
#include <unordered_map>

#include "common.h"
#include "../logger.h"

GLAB_NAMESPACE_BEGIN()

struct Resource;

class ResourceManager {
public:
    static ResourceManager& get() noexcept;

    ~ResourceManager();

    template <typename T>
    void load(std::string_view path, std::function<void(ResourceHandle<T>)> callback) {
        if constexpr (std::is_same_v<Mesh, T>) {
            loadMesh(path, callback);
        } else if constexpr (std::is_same_v<Shader, T>) {
            loadShader(path, callback);
        } else {
            LOG_WARN("Attempting to load an unsupported resource: {}", path);
        }
    }

    void pushDestroyQueue(Resource* resource);
    void flushDestroyQueue();

private:
    void loadMesh(std::string_view path, std::function<void(ResourceHandle<Mesh>)> callback);
    void loadShader(std::string_view path, std::function<void(ResourceHandle<Shader>)> callback);

private:
    std::mutex m_mutex;
    std::queue<Resource*> m_destroy_queue;

    std::unordered_map<std::string, ResourceHandle<Mesh>> m_mesh_map;
    std::unordered_map<std::string, ResourceHandle<Shader>> m_shader_map;
};

template void ResourceManager::load<Mesh>(std::string_view path,
                                          std::function<void(ResourceHandle<Mesh>)> callback);
template void ResourceManager::load<Shader>(std::string_view path,
                                            std::function<void(ResourceHandle<Shader>)> callback);

GLAB_NAMESPACE_END()
