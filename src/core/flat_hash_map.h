#pragma once

#include <unordered_map>
#include <vector>

namespace glab::core {

template <typename K, typename V>
struct FlatHashMap {
    V* Get(const K& key) {
        if (auto it = m_key_index_map.find(key); it != m_key_index_map.end()) {
            return &m_values[it->second].second;
        }
        return nullptr;
    }

    const V* Get(const K& key) const {
        if (auto it = m_key_index_map.find(key); it != m_key_index_map.end()) {
            return &m_values[it->second].second;
        }
        return nullptr;
    }

    void Insert(const K& key, const V& value) {
        if (m_key_index_map.contains(key)) {
            return;
        }
        m_key_index_map[key] = m_values.size();
        m_values.emplace_back(key, value);
    }

    void Insert(const K& key, V&& value) {
        if (m_key_index_map.contains(key)) {
            return;
        }
        m_key_index_map[key] = m_values.size();
        m_values.emplace_back(key, std::move(value));
    }

    void InsertOrAssign(const K& key, const V& value) {
        if (auto it = m_key_index_map.find(key); it != m_key_index_map.end()) {
            m_values[it->second].second = value;
        } else {
            m_key_index_map[key] = m_values.size();
            m_values.emplace_back(key, value);
        }
    }

    void InsertOrAssign(const K& key, V&& value) {
        if (auto it = m_key_index_map.find(key); it != m_key_index_map.end()) {
            m_values[it->second].second = std::move(value);
        } else {
            m_key_index_map[key] = m_values.size();
            m_values.emplace_back(key, std::move(value));
        }
    }

    template <typename... Args>
    void Emplace(const K& key, Args&&... args) {
        if (m_key_index_map.contains(key)) {
            return;
        }
        m_key_index_map[key] = m_values.size();
        m_values.emplace_back(key, V(std::forward<Args>(args)...));
    }

    void Erase(const K& key) {
        using std::swap;

        if (auto it = m_key_index_map.find(key); it != m_key_index_map.end()) {
            auto index = it->second;
            auto last_index = m_values.size() - 1;

            if (index != last_index) {
                swap(m_values[index], m_values[last_index]);
                m_key_index_map[m_values[index].first] = index;
            }
            m_values.pop_back();
            m_key_index_map.erase(it);
        }
    }

    bool Empty() const { return m_values.empty(); }

    std::size_t Size() const { return m_values.size(); }

    void Clear() {
        m_values.clear();
        m_key_index_map.clear();
    }

private:
    std::vector<std::pair<K, V>> m_values;
    std::unordered_map<K, std::size_t> m_key_index_map;
};

}  // namespace glab::core
