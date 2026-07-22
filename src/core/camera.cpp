#include "camera.h"

#include <glm/ext/matrix_clip_space.hpp>

GLAB_NAMESPACE_BEGIN()

void Camera::updateViewMatrix(const glm::mat4& camera_world_matrix) {
    view_matrix = glm::inverse(camera_world_matrix);
    view_projection_matrix = projection_matrix * view_matrix;
}

void Camera::updateProjectionMatrix() {
    if (type == CameraType::Orthographics) {
        projection_matrix = glm::ortho(left, right, bottom, top);
    } else {
        projection_matrix = glm::perspective(glm::radians(fovy), aspect, near, far);
    }
}

GLAB_NAMESPACE_END()
