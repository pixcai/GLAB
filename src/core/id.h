#pragma once

#include <functional>

namespace glab::core {

template <typename T>
struct ID {
    std::size_t value{++next_value};

    bool operator==(const ID& other) const = default;

    void Reset() { value = 0; }
    bool IsValid() const { return value != 0; }

private:
    inline static std::size_t next_value;
};

template <typename T>
struct ResourceID : public ID<T> {};

}  // namespace glab::core

template <typename T>
struct std::hash<glab::core::ID<T>> {
    std::size_t operator()(const glab::core::ID<T>& id) const noexcept { return std::hash<std::size_t>{}(id.value); }
};

template <typename T>
struct std::hash<glab::core::ResourceID<T>> {
    std::size_t operator()(const glab::core::ResourceID<T>& id) const noexcept {
        return std::hash<std::size_t>{}(id.value);
    }
};
