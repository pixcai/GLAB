#include "geometry_helpers.h"
#include "vertex.h"

#include <utility>
#include <vector>

#include <glm/glm.hpp>

namespace glab::mesh {

Geometry GeometryHelpers::MakeCube(float size) {
    float half_size{size / 2.0f};
    glm::vec3 vf00{-half_size, -half_size, half_size};
    glm::vec3 vf10{half_size, -half_size, half_size};
    glm::vec3 vf11{half_size, half_size, half_size};
    glm::vec3 vf01{-half_size, half_size, half_size};
    glm::vec3 vb00{-half_size, -half_size, -half_size};
    glm::vec3 vb10{half_size, -half_size, -half_size};
    glm::vec3 vb11{half_size, half_size, -half_size};
    glm::vec3 vb01{-half_size, half_size, -half_size};
    glm::vec3 nx{1.0f, 0.0f, 0.0f}, ny{0.0f, 1.0f, 0.0f}, nz{0.0f, 0.0f, 1.0f};
    glm::vec2 uv00{0.0f, 0.0f}, uv10{1.0f, 0.0f}, uv11{1.0f, 1.0f}, uv01{0.0f, 1.0f};
    std::vector<Vertex> vertices;

    // Front - BottomLeft
    vertices.emplace_back(vf00, nz, uv00);
    // Front - BottomRight
    vertices.emplace_back(vf10, nz, uv10);
    // Front - TopRight
    vertices.emplace_back(vf11, nz, uv11);
    // Front - TopLeft
    vertices.emplace_back(vf01, nz, uv01);
    // Back - BottomLeft
    vertices.emplace_back(vb00, -nz, uv00);
    // Back - BottomRight
    vertices.emplace_back(vb10, -nz, uv10);
    // Back - TopRight
    vertices.emplace_back(vb11, -nz, uv11);
    // Back - TopLeft
    vertices.emplace_back(vb01, -nz, uv01);
    // Right - BottomLeft
    vertices.emplace_back(vf10, nx, uv00);
    // Right - BottomRight
    vertices.emplace_back(vb10, nx, uv10);
    // Right - TopRight
    vertices.emplace_back(vb11, nx, uv11);
    // Right - TopLeft
    vertices.emplace_back(vf11, nx, uv01);
    // Left - BottomLeft
    vertices.emplace_back(vf00, -nx, uv00);
    // Left - BottomRight
    vertices.emplace_back(vb00, -nx, uv10);
    // Left - TopRight
    vertices.emplace_back(vb01, -nx, uv11);
    // Left - TopLeft
    vertices.emplace_back(vf01, -nx, uv01);
    // Top - BottomLeft
    vertices.emplace_back(vf01, ny, uv00);
    // Top - BottomRight
    vertices.emplace_back(vf11, ny, uv10);
    // Top - TopRight
    vertices.emplace_back(vb11, ny, uv11);
    // Top - TopLeft
    vertices.emplace_back(vb01, ny, uv01);
    // Bottom - BottomLeft
    vertices.emplace_back(vf00, -ny, uv00);
    // Bottom - BottomRight
    vertices.emplace_back(vf10, -ny, uv10);
    // Bottom - TopRight
    vertices.emplace_back(vb10, -ny, uv11);
    // Bottom - TopLeft
    vertices.emplace_back(vb00, -ny, uv01);

    // clang-format off
    return {
        std::move(vertices),
        {
            // Front
            0, 1, 2, 2, 3, 0,
            // Back
            4, 5, 6, 6, 7, 4,
            // Right
            8, 9, 10, 10, 11, 8,
            // Left
            12, 13, 14, 14, 15, 12,
            // Top
            16, 17, 18, 18, 19, 16,
            // Bottom
            20, 21, 22, 22, 23, 20,
         }
    };
    // clang-format on
}

}  // namespace glab::mesh
