#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace glab::scene {

struct Transform {
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};

    glm::mat4 local_matrix{1.0f};
    glm::mat4 world_matrix{1.0f};

    glm::vec3 forward() const noexcept { return rotation * glm::vec3(0.0f, 0.0f, -1.0f); }

    void lookAt(glm::vec3 target, glm::vec3 up = {0.0f, 1.0f, 0.0f}) {
        auto direction = glm::normalize(target - position);
        rotation = glm::quatLookAt(direction, up);
    }

    void updateLocalMatrix() {
        local_matrix =
            glm::translate(glm::mat4(1.0f), position) * glm::mat4(rotation) * glm::scale(glm::mat4(1.0f), scale);
    }

    void updateWorldMatrix(const glm::mat4& parent_matrix) {
        updateLocalMatrix();
        world_matrix = parent_matrix * local_matrix;
    }
};

}  // namespace glab::scene
