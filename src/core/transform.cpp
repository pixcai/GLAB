#include "transform.h"

#include <glm/ext/matrix_transform.hpp>

GLAB_NAMESPACE_BEGIN()

void Transform::lookAt(glm::vec3 target, glm::vec3 up) {
    auto view_matrix = glm::lookAt(position, target, up);
}

void Transform::updateLocalMatrix() {
    local_matrix = glm::translate(glm::mat4(1.0f), position) * glm::mat4(rotation) *
                   glm::scale(glm::mat4(1.0f), scale);
}

void Transform::updateWorldMatrix(const glm::mat4& parent_matrix) {
    updateLocalMatrix();
    world_matrix = parent_matrix * local_matrix;
}

GLAB_NAMESPACE_END()
