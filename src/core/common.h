#pragma once

#include <cstdint>
#include <limits>

#include "../namespace.h"

GLAB_NAMESPACE_BEGIN()

class Scene;
class Renderer;

struct Entity {
    static constexpr auto INVALID_ID = std::numeric_limits<std::uint32_t>::max();

    std::uint32_t id{INVALID_ID};
    std::uint32_t generation{0};

    bool operator==(const Entity& other) const noexcept {
        return id == other.id && generation == other.generation;
    }

    bool valid() const noexcept { return id != INVALID_ID; }
};

struct IComponent {
    IComponent() = default;
    virtual ~IComponent() = default;
};

struct Mesh;
struct Shader;

template <typename T>
class ResourceHandle;

GLAB_NAMESPACE_END()
