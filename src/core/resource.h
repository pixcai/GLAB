#pragma once

#include <concepts>
#include <string>

#include "resource_manager.h"

GLAB_NAMESPACE_BEGIN()

enum class ResourceType {
    Mesh,
    Shader,
};

struct IResource {
    ResourceType resource_type;
    std::string resource_path;

    IResource(ResourceType type) : resource_type(type) {}
    virtual ~IResource() = default;

    virtual void destroy() = 0;

private:
    std::uint32_t m_ref_count{0};

    template <typename T>
    friend class ResourceHandle;
};

template <typename T>
class ResourceHandle {
public:
    // Without a default constructor, we cannot declare an uninitialized object
    // e.g. ResourceHandle<Mesh> mesh_handle; // Error
    ResourceHandle() = default;
    ~ResourceHandle() { release(); }

    explicit ResourceHandle(T* resource)
        requires std::derived_from<T, IResource>
    {
        m_resource = resource;
        if (m_resource) {
            m_resource->m_ref_count++;
        }
    }

    ResourceHandle(const ResourceHandle& other) {
        m_resource = other.m_resource;
        if (m_resource) {
            m_resource->m_ref_count++;
        }
    }

    ResourceHandle& operator=(const ResourceHandle& other) {
        release();
        m_resource = other.m_resource;
        if (m_resource) {
            m_resource->m_ref_count++;
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

    bool valid() const noexcept { return m_resource == nullptr; }

    T* get() const noexcept { return m_resource; }

    void release() {
        if (m_resource) {
            if (--m_resource->m_ref_count == 0) {
                ResourceManager::get().pushDestroyQueue(m_resource);
            }
            m_resource = nullptr;
        }
    }

private:
    T* m_resource{nullptr};
};

GLAB_NAMESPACE_END()
