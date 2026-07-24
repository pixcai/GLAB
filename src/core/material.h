#pragma once

#include <string_view>
#include <vector>

#include "resource.h"
#include "shader_manager.h"

GLAB_NAMESPACE_BEGIN()

struct Material : IResource {
    ShaderType shader_type{ShaderType::Bundle};
    ShaderFeatureBits shader_features{ShaderFeature_Lighting};

    Material() : IResource(ResourceType::Material) {}

    Shader& shader() { return ShaderManager::instance().get(shader_type, shader_features); }

    template <typename ValueType>
    void set(std::string_view name, const ValueType& value) {}

    template <typename ValueType>
    ValueType* get(std::string_view name) {
        return nullptr;
    }

    void setTexture(std::string_view name, GLint texture_id) {}

    void destroy() override {}

private:
    std::vector<std::byte> m_data;
};

GLAB_NAMESPACE_END()
