#pragma once

#include <functional>
#include <limits>

namespace glab::core {

template <typename T>
struct ID {
    using Index = std::size_t;
    using Generation = std::size_t;

    static constexpr Index kInvalidIndex = std::numeric_limits<Index>::max();

    Index index{kInvalidIndex};
    Generation generation{0};

    bool operator==(const ID& other) const = default;

    void Reset() {
        index = kInvalidIndex;
        generation = 0;
    }

    bool IsValid() const { return index != kInvalidIndex; }
};

template <typename T>
struct IDPool {
    using Index = ID<T>::Index;
    using Generation = ID<T>::Generation;

    ID<T> Allocate() {
        Index index;

        if (m_next_index != ID<T>::kInvalidIndex) {
            index = m_next_index;

            auto& slot = m_slots[index];

            m_next_index = slot.next_index;
            slot.next_index = ID<T>::kInvalidIndex;
            slot.occupied = true;
        } else {
            index = m_slots.size();
            m_slots.emplace_back(true);
        }
        return {index, m_slots[index].generation};
    }

    void Deallocate(ID<T> id) {
        if (!Contains(id)) {
            return;
        }

        auto& slot = m_slots[id.index];

        slot.occupied = false;
        slot.next_index = m_next_index;
        ++slot.generation;
        m_next_index = id.index;
    }

    bool Contains(ID<T> id) const {
        if (!id.IsValid() || id.index >= m_slots.size()) {
            return false;
        }
        auto& slot = m_slots[id.index];
        return slot.occupied && slot.generation == id.generation;
    }

private:
    struct Slot {
        bool occupied{false};
        Index next_index{ID<T>::kInvalidIndex};
        Generation generation{0};
    };

    std::vector<Slot> m_slots;
    Index m_next_index{ID<T>::kInvalidIndex};
};

}  // namespace glab::core

template <typename T>
struct std::hash<glab::core::ID<T>> {
    std::size_t operator()(const glab::core::ID<T>& id) const noexcept {
        auto h1 = std::hash<typename glab::core::ID<T>::Index>{}(id.index);
        auto h2 = std::hash<typename glab::core::ID<T>::Generation>{}(id.generation);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};
