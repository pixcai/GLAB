#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "../gl.h"
#include "../namespace.h"

GLAB_NAMESPACE_BEGIN()

enum class ShaderLayoutType {
    UniformBuffer,
    Sampler,
};

enum class ShaderFieldType {
    Float,
    Vec3,
    Mat4x4,
};

struct ShaderLayoutField {
    ShaderFieldType type;
    std::string name;
    std::uint32_t offset;
    std::uint32_t size;
};

struct ShaderLayout {
    ShaderLayoutType type{ShaderLayoutType::UniformBuffer};
    std::string name;
    std::uint32_t size;
    std::uint32_t binding;
    std::vector<ShaderLayoutField> fields;
};

class Shader {
public:
    GLuint program{0};
    std::vector<ShaderLayout> layouts;

private:
    void destroy() {
        if (program) {
            glDeleteProgram(program);
        }
        program = 0;
        layouts.clear();
    }

    friend class ShaderManager;
};

using ShaderFeatureBits = std::uint32_t;

constexpr ShaderFeatureBits ShaderFeature_None = 0;
constexpr ShaderFeatureBits ShaderFeature_Lighting = 1;

enum class ShaderType {
    Bundle,
    Wireframe,
};

class ShaderManager {
public:
    static ShaderManager& instance() noexcept {
        static ShaderManager singleton;
        return singleton;
    }

    ~ShaderManager();

    void init();
    Shader& get(ShaderType type, ShaderFeatureBits features);

private:
    Shader compile(ShaderType type, ShaderFeatureBits features);

private:
    std::unordered_map<uint64_t, Shader> m_shader_map;
};

GLAB_NAMESPACE_END()
