#include "config/config.h"
#include "shader_manager.h"

#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <glad/gl.h>
#include <spdlog/spdlog.h>

#define STB_INCLUDE_IMPLEMENTATION
#define STB_INCLUDE_LINE_GLSL
#include <stb_include.h>

namespace glab::rendering {

namespace {

std::unordered_map<ShaderFeature, std::string> g_feature_macros = {
    {ShaderFeature::Texture, "USE_TEXTURE"},
    {ShaderFeature::Lighting, "USE_LIGHTING"},
};

GLuint Compile(GLenum type, const char* source) {
    auto shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    char error[256];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(shader, sizeof(error), nullptr, error);
        throw std::runtime_error(error);
    }
    return shader;
}

GLuint CompileFiles(std::vector<std::pair<GLenum, std::string>>& files, ShaderFeature features) {
    GLint success;
    char error[256];
    std::vector<GLuint> shaders;

    for (auto& [type, path] : files) {
        std::ifstream file{config::kShaderRoot / path};
        if (!file.is_open()) {
            throw std::runtime_error(std::format("Failed to open GLSL file: {}", path));
        }

        std::ostringstream code;

        code << '\n' << config::kGLSLVersionString << '\n';
        for (auto& [feature, macro] : g_feature_macros) {
            if ((features & feature) != ShaderFeature::None) {
                code << std::format("#define {}", macro) << '\n';
            }
        }
        code << file.rdbuf();

        auto source =
            stb_include_string(code.str().data(), nullptr, config::kShaderRoot.string().data(), path.data(), error);
        spdlog::debug(source);
        if (!source) {
            throw std::runtime_error(error);
        }

        try {
            shaders.push_back(Compile(type, source));
            std::free(source);
        } catch (...) {
            std::free(source);
            for (auto shader : shaders) {
                glDeleteShader(shader);
            }
            throw;
        }
    }

    auto program = glCreateProgram();

    for (auto shader : shaders) {
        glAttachShader(program, shader);
    }
    glLinkProgram(program);
    for (auto shader : shaders) {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        glGetProgramInfoLog(program, sizeof(error), nullptr, error);
        glDeleteProgram(program);
        throw std::runtime_error(error);
    }
    return program;
}

}  // namespace

void ShaderManager::Set(std::string name, std::vector<std::pair<GLenum, std::string>> files) {
    m_files.emplace(name, std::move(files));
}

Shader* ShaderManager::Get(std::string name, ShaderFeature features) {
    if (!m_files.contains(name)) {
        spdlog::error("Shader key not found: {}", name);
        return nullptr;
    }

    auto key = std::format("{}:{}", name, static_cast<std::uint32_t>(features));

    if (!m_shaders.contains(key)) {
        try {
            m_shaders.emplace(key, CompileFiles(m_files[name], features));
        } catch (const std::exception& e) {
            spdlog::error("Failed to compile shader: {}", e.what());
            return nullptr;
        }
    }
    return &m_shaders.at(key);
}

}  // namespace glab::rendering
