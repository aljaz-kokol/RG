#include "Rotation.h"
#include "glm/gtc/matrix_transform.hpp"

Rotation::Rotation(float angle, const glm::vec3 &factors)
: angles(angle), axis(factors) {}

glm::mat4 Rotation::transform() const {
    glm::mat4 model(1);
    model = glm::rotate(model, glm::radians(angles.x), {axis.x, 0, 0});
    model = glm::rotate(model, glm::radians(angles.y), {0, axis.y, 0});
    model = glm::rotate(model, glm::radians(angles.z), {0, 0, axis.z});
    return model;
}

const glm::vec3 &Rotation::getAxis() const {
    return axis;
}

void Rotation::setAxis(const glm::vec3 &axis) {
    Rotation::axis = axis;
}

const glm::vec3 &Rotation::getAngles() const {
    return angles;
}

void Rotation::setAngles(const glm::vec3 &angles) {
    Rotation::angles = angles;
}

void Rotation::setXAngle(float angle) {
    angles = {angle, angles.y, angles.z};
}

void Rotation::setYAngle(float angle) {
    angles = {angles.x, angle, angles.z};
}

void Rotation::setZAngle(float angle) {
    angles = {angles.x, angles.y, angle};
}
