#include "Rotation.h"
#include "glm/gtc/matrix_transform.hpp"

Rotation::Rotation(float angle, const glm::vec3 &factors)
: angle(angle), factors(factors) {}

glm::mat4 Rotation::transform() const {
    glm::mat4 model(1);
    return glm::rotate(model, glm::radians(angle), factors);
}