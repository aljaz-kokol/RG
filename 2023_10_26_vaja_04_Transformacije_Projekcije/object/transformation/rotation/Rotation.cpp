#include "Rotation.h"
#include "glm/gtc/matrix_transform.hpp"

Rotation::Rotation(float angle, const glm::vec3 &factors)
: angle(angle), axis(factors) {}

glm::mat4 Rotation::transform() const {
    glm::mat4 model(1);
    return glm::rotate(model, glm::radians(angle), axis);
}

const glm::vec3 &Rotation::getAxis() const {
    return axis;
}

void Rotation::setAxis(const glm::vec3 &axis) {
    Rotation::axis = axis;
}

float Rotation::getAngle() const {
    return angle;
}

void Rotation::setAngle(float angle) {
    Rotation::angle = angle;
}
