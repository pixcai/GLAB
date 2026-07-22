#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../namespace.h"

GLAB_NAMESPACE_BEGIN()

struct Transform {
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    glm::quat rotation{0.0f, 0.0f, 0.0f, 1.0f};

    glm::mat4 local_matrix{1.0f};
    glm::mat4 world_matrix{1.0f};

    void lookAt(glm::vec3 target, glm::vec3 up = {0.0f, 1.0f, 0.0f});
    void updateLocalMatrix();
    void updateWorldMatrix(const glm::mat4& parent_matrix);
};

GLAB_NAMESPACE_END()
