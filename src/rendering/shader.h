#pragma once

#include "core/id.h"

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace glab::rendering {

using UniformValue = std::variant<int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4>;

struct Uniform {
    std::string name;
    std::string display_name;
    GLenum type;
    GLint location{-1};
};

struct UniformBlock {
    std::string name;
    GLuint binding;
    GLuint index{GL_INVALID_INDEX};
};

inline std::vector<Uniform> g_uniforms = {
    {"model_matrix", "Model Matrix", GL_FLOAT_MAT4},
    {"view_matrix", "View Matrix", GL_FLOAT_MAT4},
    {"projection_matrix", "Projection Matrix", GL_FLOAT_MAT4},
};

inline std::vector<UniformBlock> g_uniform_blocks = {};

class Shader;

using ShaderID = core::ID<Shader>;

enum class ShaderType : std::uint8_t {
    kBasic,
    kPBR,
};

class Shader {
public:
    Shader(GLuint program);
    ~Shader();

    Shader(const Shader& other) = delete;
    Shader& operator=(const Shader& other) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void Use() const;

    const std::unordered_map<std::string, Uniform>& GetUniforms() const { return m_uniforms; }
    void SetUniform(std::string name, const UniformValue& value) const;

    const std::unordered_map<std::string, UniformBlock>& GetUniformBlocks() const { return m_uniform_blocks; }

private:
    GLuint m_program;
    std::unordered_map<std::string, Uniform> m_uniforms;
    std::unordered_map<std::string, UniformBlock> m_uniform_blocks;
};

}  // namespace glab::rendering
