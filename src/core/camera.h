#pragma once

#include <glm/glm.hpp>

#include "../namespace.h"

GLAB_NAMESPACE_BEGIN()

enum class CameraType {
    Perspective,
    Orthographics,
};

struct Camera {
    CameraType type{CameraType::Perspective};

    float near{0.01f};
    float far{100.0f};

    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;
    glm::mat4 view_projection_matrix;

    // Perspective camera fields
    float fovy{60.0f};
    float aspect{16.0f / 9.0f};

    // Orthographics camera fields
    float left{0.0f}, right{0.0f}, bottom{0.0f}, top{0.0f};

    bool active{true};

    void updateViewMatrix(const glm::mat4& camera_world_matrix);
    void updateProjectionMatrix();
};

GLAB_NAMESPACE_END()
