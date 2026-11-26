#pragma once

#include "core/flat_hash_map.h"
#include "core/id.h"

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace glab {

enum class ResourceStatus {
    kLoading,
    kReady,
    kUnloading,
};

template <typename T>
struct Resource {
    std::unique_ptr<T> data;
    int ref_count{1};
    ResourceStatus status{ResourceStatus::kReady};
};

struct IResourceStore {
    virtual ~IResourceStore() = default;
};

template <typename T>
struct ResourceStore : public IResourceStore {
    inline static core::IDPool<T> id_pool;
    core::FlatHashMap<core::ID<T>, Resource<T>> resources;
};

class ResourceManager {
public:
    template <typename T>
    T* Acquire(core::ID<T> id) {
        if (auto store = GetStore<T>()) {
            if (auto resource = store->resources.Get(id); resource != nullptr) {
                ++resource->ref_count;
                return resource->data.get();
            }
        }
        return nullptr;
    }

    template <typename T>
    void Release(core::ID<T> id) {
        if (auto store = GetStore<T>()) {
            if (auto resource = store->resources.Get(id); resource != nullptr) {
                if (--resource->ref_count <= 0) {
                    ResourceStore<T>::id_pool.Deallocate(id);
                    store->resources->Erase(id);
                }
            }
        }
    }

    template <typename T>
    T* TryGet(core::ID<T> id) {
        if (auto store = GetStore<T>()) {
            if (auto resource = store->resources.Get(id); resource != nullptr) {
                return resource->data.get();
            }
        }
        return nullptr;
    }

    template <typename T>
    core::ID<T> Add(T&& data) {
        auto store = GetStore<T>();
        auto id = ResourceStore<T>::id_pool.Allocate();

        if (!store) {
            m_stores.try_emplace(typeid(T), std::make_unique<ResourceStore<T>>());
            store = GetStore<T>();
        }
        store->resources.Insert(id, std::make_unique<T>(std::forward<T>(data)));
        return id;
    }

    template <typename T, typename... Args>
    core::ID<T> Create(Args&&... args) {
        auto store = GetStore<T>();
        auto id = ResourceStore<T>::id_pool.Allocate();

        if (!store) {
            m_stores.try_emplace(typeid(T), std::make_unique<ResourceStore<T>>());
            store = GetStore<T>();
        }
        store->resources.Emplace(id, std::make_unique<T>(std::forward<Args>(args)...));
        return id;
    }

private:
    template <typename T>
    ResourceStore<T>* GetStore() {
        if (auto it = m_stores.find(typeid(T)); it != m_stores.end()) {
            return static_cast<ResourceStore<T>*>(it->second.get());
        }
        return nullptr;
    }

    std::unordered_map<std::type_index, std::unique_ptr<IResourceStore>> m_stores;
};

inline ResourceManager resource_manager;

}  // namespace glab
