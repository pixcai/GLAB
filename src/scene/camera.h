#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

namespace glab::scene {

enum class CameraType {
    Perspective,
    Orthographics,
};

struct Camera {
    CameraType type{CameraType::Perspective};

    glm::mat4 view_matrix{1.0f};
    glm::mat4 projection_matrix{1.0f};
    glm::mat4 view_projection_matrix{1.0f};

    glm::vec3 target{0.0f, 0.0f, 0.0f};
    float yaw{0.0f}, pitch{0.0f};

    float near_plane{0.1f};
    float far_plane{1000.0f};

    // Perspective camera fields
    float fovy{45.0f};
    int width{1}, height{1};

    // Orthographics camera fields
    float left{-1.0f}, right{1.0f}, bottom{-1.0f}, top{1.0f};

    bool active{true};

    Camera() {
        view_matrix = glm::lookAt(glm::vec3{0.0f, 4.0f, 8.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
        updateProjectionMatrix();
    }

    void updateViewMatrix(const glm::mat4& camera_world_matrix) {
        view_matrix = glm::inverse(camera_world_matrix);
        view_projection_matrix = projection_matrix * view_matrix;
    }

    void updateProjectionMatrix() {
        if (type == CameraType::Orthographics) {
            projection_matrix = glm::ortho(left, right, bottom, top);
        } else {
            projection_matrix = glm::perspective(glm::radians(fovy), (float)width / height, near_plane, far_plane);
        }
        view_projection_matrix = projection_matrix * view_matrix;
    }
};

}  // namespace glab::scene
