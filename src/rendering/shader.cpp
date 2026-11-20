#include "shader.h"

#include <utility>

#include <glad/gl.h>
#include <spdlog/spdlog.h>
#include <glm/gtc/type_ptr.hpp>

namespace glab::rendering {

Shader::Shader(GLuint program) : m_program(program) {
    for (const auto& uniform : g_uniforms) {
        auto location = glGetUniformLocation(m_program, uniform.name.c_str());
        if (location != -1) {
            m_uniforms[uniform.name] = uniform;
            m_uniforms[uniform.name].location = location;
            spdlog::debug("uniform = {}, location = {}", uniform.name, location);
        }
    }
    for (const auto& uniform_block : g_uniform_blocks) {
        auto index = glGetUniformBlockIndex(m_program, uniform_block.name.c_str());
        if (index != GL_INVALID_INDEX) {
            m_uniform_blocks[uniform_block.name] = uniform_block;
            m_uniform_blocks[uniform_block.name].index = index;
            glUniformBlockBinding(m_program, index, uniform_block.binding);
            spdlog::debug("uniform_block = {}, binding={}, index = {}", uniform_block.name, uniform_block.binding,
                          index);
        }
    }
}

Shader::Shader(Shader&& other) noexcept
    : m_program(std::exchange(other.m_program, 0))
    , m_uniforms(std::move(other.m_uniforms))
    , m_uniform_blocks(std::move(other.m_uniform_blocks)) {}

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    if (m_program) {
        glDeleteProgram(m_program);
    }
    m_program = std::exchange(other.m_program, 0);
    m_uniforms = std::move(other.m_uniforms);
    m_uniform_blocks = std::move(other.m_uniform_blocks);
    return *this;
}
Shader::~Shader() { glDeleteProgram(m_program); }

void Shader::Use() const { glUseProgram(m_program); }

void Shader::SetUniform(std::string name, const UniformValue& value) const {
    if (!m_uniforms.contains(name)) {
        return;
    }

    auto uniform = m_uniforms.at(name);

    switch (uniform.type) {
        case GL_INT:
            glUniform1i(uniform.location, std::get<int>(value));
            break;
        case GL_FLOAT:
            glUniform1f(uniform.location, std::get<float>(value));
            break;
        case GL_FLOAT_VEC2:
            glUniform2fv(uniform.location, 1, glm::value_ptr(std::get<glm::vec2>(value)));
            break;
        case GL_FLOAT_VEC3:
            glUniform2fv(uniform.location, 1, glm::value_ptr(std::get<glm::vec3>(value)));
            break;
        case GL_FLOAT_VEC4:
            glUniform2fv(uniform.location, 1, glm::value_ptr(std::get<glm::vec4>(value)));
            break;
        case GL_FLOAT_MAT3:
            glUniformMatrix3fv(uniform.location, 1, GL_FALSE, glm::value_ptr(std::get<glm::mat3>(value)));
            break;
        case GL_FLOAT_MAT4:
            glUniformMatrix4fv(uniform.location, 1, GL_FALSE, glm::value_ptr(std::get<glm::mat4>(value)));
            break;
    }
}

}  // namespace glab::rendering
