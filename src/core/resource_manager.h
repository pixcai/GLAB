#pragma once

#include <functional>
#include <mutex>
#include <queue>
#include <string>
#include <unordered_map>

#include "common.h"

GLAB_NAMESPACE_BEGIN()

struct Resource;

class ResourceManager {
public:
    static ResourceManager& get() noexcept;

    ~ResourceManager();

    template <typename T>
    void load(const std::string& path, std::function<void(ResourceHandle<T>)> callback);

    void pushDestroyQueue(Resource* resource);
    void flushDestroyQueue();

private:
    std::mutex m_mutex;
    std::queue<Resource*> m_destroy_queue;

    std::unordered_map<std::string, ResourceHandle<Mesh>> m_mesh_map;
    std::unordered_map<std::string, ResourceHandle<Shader>> m_shader_map;
};

GLAB_NAMESPACE_END()
