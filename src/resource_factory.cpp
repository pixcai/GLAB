#include "mesh/geometry_helpers.h"
#include "mesh/mesh.h"
#include "rendering/material.h"
#include "rendering/shader.h"
#include "rendering/shader_manager.h"
#include "resource_factory.h"
#include "resource_manager.h"

namespace glab {

mesh::MeshID ResourceFactory::CreateCube(float size) {
    auto [vertices, indices] = mesh::GeometryHelpers::MakeCube(size);
    return resource_manager.Create<mesh::Mesh>(std::move(vertices), std::move(indices));
}

rendering::MaterialID ResourceFactory::CreateMaterial() {
    return resource_manager.Create<rendering::Material>(rendering::ShaderType::kPBR, rendering::ShaderFeature::Lighting,
                                                        glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}, 0.5f, 0.5f, 0.5f);
}

}  // namespace glab
