#include "Scale.h"
#include "glm/gtc/matrix_transform.hpp"

Scale::Scale(const glm::vec3& factors): factors(factors) {}
Scale::Scale(float factor): factors(glm::vec3(factor, factor, factor)) {}

glm::mat4 Scale::transform() const {
    glm::mat4 model(1);
    return glm::scale(model, factors);
}

const glm::vec3 &Scale::getFactors() const {
    return factors;
}

void Scale::setFactors(const glm::vec3 &factors) {
    Scale::factors = factors;
}
