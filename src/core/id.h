#pragma once

#include <functional>

namespace glab::core {

template <typename T>
struct ID {
    static ID Next() { return {++next_value}; }

    std::size_t value{};

    bool operator==(const ID& other) const = default;

    constexpr bool IsValid() const { return value != 0; }

private:
    inline static std::size_t next_value{};
};

}  // namespace glab::core

namespace std {

template <typename T>
struct hash<glab::core::ID<T>> {
    std::size_t operator()(const glab::core::ID<T>& id) const noexcept { return std::hash<std::size_t>{}(id.value); }
};

}  // namespace std
