#pragma once

#include "core/id.h"
#include "shader.h"

#include <glm/glm.hpp>

namespace glab::rendering {

struct Material;

using MaterialID = core::ID<Material>;

struct Material {
    ShaderID shader_id;
    glm::vec4 base_color;
    float albedo;
    float metalic;
    float roughness;
};

}  // namespace glab::rendering
