#pragma once

#include <glm/glm.hpp>

#include "common.h"

GLAB_NAMESPACE_BEGIN()

enum class CameraType {
    Perspective,
    Orthographics,
};

struct Camera : IComponent {
    CameraType type{CameraType::Perspective};

    float near{0.1f};
    float far{1000.0f};

    glm::mat4 view_matrix{1.0f};
    glm::mat4 projection_matrix{1.0f};
    glm::mat4 view_projection_matrix{1.0f};

    // Perspective camera fields
    float fovy{45.0f};
    float aspect{16.0f / 9.0f};

    // Orthographics camera fields
    float left{-1.0f}, right{1.0f}, bottom{-1.0f}, top{1.0f};

    bool active{true};

    void updateViewMatrix(const glm::mat4& camera_world_matrix);
    void updateProjectionMatrix();
};

GLAB_NAMESPACE_END()
