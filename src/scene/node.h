#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace glab::scene {

class Scene;

using NodeID = std::size_t;
inline constexpr NodeID VALID_NODE_ID = 0;

class Node;

struct BucketBase {
    virtual ~BucketBase() = default;
};

template <typename ComponentT>
struct Bucket : public BucketBase {
    std::vector<ComponentT> components;
    std::unordered_map<NodeID, std::size_t> indices;
};

class Storage {
public:
    template <typename ComponentT>
    std::vector<ComponentT>* GetAll() const {
        auto bucket = GetBucket<ComponentT>();

        if (!bucket) {
            return nullptr;
        }
        return bucket->components;
    }

    template <typename ComponentT>
    ComponentT* Get(NodeID node_id) const {
        auto bucket = GetBucket<ComponentT>();

        if (!(bucket && bucket->indices.contains(node_id))) {
            return nullptr;
        }
        return &bucket->components[bucket->indices[node_id]];
    }

    template <typename ComponentT, typename... Args>
    ComponentT& Add(NodeID node_id, Args&&... args) {
        auto bucket = GetBucket<ComponentT>();

        if (!bucket) {
            m_buckets.emplace(typeid(ComponentT), std::make_unique<Bucket<ComponentT>>());
            bucket = GetBucket<ComponentT>();
        }
        bucket->components.emplace_back(std::forward<Args>(args)...);
        bucket->indices.emplace(node_id, bucket->components.size() - 1);
        return bucket->components[bucket->indices[node_id]];
    }

    template <typename ComponentT>
    void Remove(NodeID node_id) {
        auto bucket = GetBucket<ComponentT>();

        if (!(bucket && bucket->indices.contains(node_id))) {
            return;
        }

        auto index = bucket->indices[node_id];
        auto last_index = bucket->components.size() - 1;

        bucket->components.swap(bucket->components[index], bucket->components.back());
        bucket->components.pop_back();
        bucket->indices.erase(node_id);
        for (auto [key, value] : bucket->indices) {
            if (value == last_index) {
                bucket->indices[key] = index;
                break;
            }
        }
    }

private:
    template <typename ComponentT>
    Bucket<ComponentT>* GetBucket() const {
        if (!m_buckets.contains(typeid(ComponentT))) {
            return nullptr;
        }
        return static_cast<Bucket<ComponentT>*>(m_buckets.at(typeid(ComponentT)));
    }

    std::unordered_map<std::type_index, std::unique_ptr<BucketBase>> m_buckets;
};

class Node : public std::enable_shared_from_this<Node> {
public:
    ~Node() = default;

    NodeID GetID() const { return m_id; }

    void AddChild(std::shared_ptr<Node> child);
    void RemoveChild(std::shared_ptr<Node> child);

    template <typename ComponentT>
    ComponentT* Get() const {
        return m_storage.Get<ComponentT>(m_id);
    }

    template <typename ComponentT, typename... Args>
    ComponentT& Add(Args&&... args) {
        return m_storage.Add<ComponentT>(m_id, std::forward<Args>(args)...);
    }

    template <typename ComponentT>
    void Remove() {
        return m_storage.Remove<ComponentT>(m_id);
    }

private:
    friend class Scene;
    Node(NodeID id, Storage& storage);

    NodeID m_id;
    Storage& m_storage;
    std::shared_ptr<Node> m_parent;
    std::unordered_map<NodeID, std::shared_ptr<Node>> m_children;
};

}  // namespace glab::scene
