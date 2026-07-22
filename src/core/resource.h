#pragma once

#include <atomic>
#include <string>

#include "common.h"
#include "resource_manager.h"

GLAB_NAMESPACE_BEGIN()

enum class ResourceType {
    None,
    Mesh,
    Shader,
};

struct Resource {
    ResourceType resource_type{ResourceType::None};
    std::string resource_path;

    virtual ~Resource() = default;
    virtual void destroy() = 0;

private:
    std::atomic_int32_t ref_count{1};

    template <typename T>
    friend class ResourceHandle;
};

template <typename T>
class ResourceHandle {
public:
    // Without a default constructor, we cannot declare an uninitialized object
    // e.g. ResourceHandle<Mesh> mesh_handle; // Error
    ResourceHandle() = default;
    explicit ResourceHandle(T* resource) : m_resource(resource) {}

    ~ResourceHandle() { release(); }

    ResourceHandle(const ResourceHandle& other) {
        m_resource = other.m_resource;
        if (m_resource) {
            m_resource->ref_count++;
        }
    }

    ResourceHandle& operator=(const ResourceHandle& other) {
        release();
        m_resource = other.m_resource;
        if (m_resource) {
            m_resource->ref_count++;
        }
        return *this;
    }

    ResourceHandle(ResourceHandle&& other) noexcept {
        m_resource = other.m_resource;
        other.m_resource = nullptr;
    }

    ResourceHandle& operator=(ResourceHandle&& other) noexcept {
        release();
        m_resource = other.m_resource;
        other.m_resource = nullptr;
        return *this;
    }

    T* operator->() const noexcept { return m_resource; }

    bool empty() const noexcept { return m_resource == nullptr; }

    T* get() const noexcept { return m_resource; }

    void release() {
        if (m_resource) {
            if (--m_resource->ref_count == 0) {
                ResourceManager::get().pushDestroyQueue(m_resource);
            }
            m_resource = nullptr;
        }
    }

private:
    T* m_resource{nullptr};
};

GLAB_NAMESPACE_END()
