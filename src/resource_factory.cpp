#include "mesh/geometry_helpers.h"
#include "mesh/mesh.h"
#include "resource_factory.h"
#include "resource_manager.h"

namespace glab {

mesh::MeshID ResourceFactory::CreateCube(float size) {
    auto [vertices, indices] = mesh::GeometryHelpers::MakeCube(size);
    return resource_manager.Create<mesh::Mesh>(std::move(vertices), std::move(indices));
}

}  // namespace glab
