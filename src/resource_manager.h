#pragma once

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
struct ResourceEntry {
    core::ID<T> id;
    std::unique_ptr<T> data;
    int ref_count{1};
    ResourceStatus status{ResourceStatus::kReady};
};

struct IResourceStore {
    virtual ~IResourceStore() = default;
};

template <typename T>
struct ResourceStore : public IResourceStore {
    ResourceEntry<T>* Get(core::ID<T> id) {
        if (auto it = m_entries.find(id); it != m_entries.end()) {
            return &it->second;
        }
        return nullptr;
    }

    template <typename... Args>
    core::ID<T> Add(Args&&... args) {
        core::ID<T> id;
        m_entries.try_emplace(id, id, std::make_unique<T>(std::forward<Args>(args)...));
        return id;
    }

    void Remove(core::ID<T> id) { m_entries.erase(id); }

private:
    std::unordered_map<core::ID<T>, ResourceEntry<T>> m_entries;
};

struct ResourceManager {
    template <typename T>
    T* Acquire(core::ID<T> id) {
        if (auto store = GetStore<T>()) {
            if (auto entry = store->Get(id); entry) {
                ++entry->ref_count;
                return entry->data.get();
            }
        }
        return nullptr;
    }

    template <typename T>
    void Release(core::ID<T> id) {
        if (auto store = GetStore<T>()) {
            if (auto entry = store->Get(id); entry) {
                if (--entry->ref_count <= 0) {
                    store->Remove(id);
                }
            }
        }
    }

    template <typename T>
    T* TryGet(core::ID<T> id) {
        if (auto store = GetStore<T>()) {
            if (auto entry = store->Get(id); entry) {
                return entry->data.get();
            }
        }
        return nullptr;
    }

    template <typename T, typename... Args>
    core::ID<T> Create(Args&&... args) {
        if (!m_stores.contains(typeid(T))) {
            m_stores.try_emplace(typeid(T), std::make_unique<ResourceStore<T>>());
        }
        return GetStore<T>()->Add(std::forward<Args>(args)...);
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

inline static ResourceManager resource_manager;

}  // namespace glab
