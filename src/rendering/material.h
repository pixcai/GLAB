#pragma once

#include "core/id.h"
#include "rendering/shader_manager.h"
#include "shader.h"

#include <glm/glm.hpp>

namespace glab::rendering {

struct Material;

using MaterialID = core::ID<Material>;

struct Material {
    ShaderType shader_type;
    ShaderFeature features;
    glm::vec4 base_color;
    float albedo;
    float metallic;
    float roughness;
};

}  // namespace glab::rendering
