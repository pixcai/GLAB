#pragma once

#include "shader.h"

#include <unordered_map>
#include <vector>

#include <glad/gl.h>

namespace glab::rendering {

enum class ShaderFeature : std::uint32_t {
    None = 0,
    Texture = 1 << 0,
    Lighting = 1 << 1,
};

constexpr ShaderFeature operator|(ShaderFeature lhs, ShaderFeature rhs) {
    return static_cast<ShaderFeature>(static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs));
}

constexpr ShaderFeature operator&(ShaderFeature lhs, ShaderFeature rhs) {
    return static_cast<ShaderFeature>(static_cast<std::uint32_t>(lhs) & static_cast<std::uint32_t>(rhs));
}

class ShaderManager {
public:
    ShaderManager() = default;
    ~ShaderManager() = default;

    ShaderManager(const ShaderManager& other) = delete;
    ShaderManager& operator=(const ShaderManager& other) = delete;

    void Set(std::string name, std::vector<std::pair<GLenum, std::string>> files);
    Shader* Get(std::string name, ShaderFeature features = ShaderFeature::None);

private:
    std::unordered_map<std::string, std::vector<std::pair<GLenum, std::string>>> m_files;
    std::unordered_map<std::string, Shader> m_shaders;
};

}  // namespace glab::rendering
