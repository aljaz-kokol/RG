#include "Rotation.h"
#include "glm/gtc/matrix_transform.hpp"

Rotation::Rotation(float angle, const glm::vec3 &factors)
: angles(angle), axis(factors) {}

Rotation::Rotation(const glm::vec3& angles, const glm::vec3 &factors)
        : angles(angles), axis(factors) {}

glm::mat4 Rotation::transform() const {
    glm::mat4 model(1);
    if (axis.y != 0) {
        model = glm::rotate(model, glm::radians(angles.y), {0, axis.y, 0 });
    }
    if (axis.x != 0) {
        model = glm::rotate(model, glm::radians(angles.x), { axis.x, 0, 0 });
    }
    if (axis.z != 0) {
        model = glm::rotate(model, glm::radians(angles.z), { 0, 0, axis.z });
    }
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

void Rotation::setAngles(const glm::vec3 &angles, const glm::vec3 &axis) {
    Rotation::angles = angles;
    Rotation::axis = axis;
}

void Rotation::setXAngle(float angle, float xAxis) {
    angles = {angle, angles.y, angles.z};
    axis.x = xAxis;
}

void Rotation::setYAngle(float angle,float yAxis) {
    angles = {angles.x, angle, angles.z};
    axis.y = yAxis;
}

void Rotation::setZAngle(float angle, float zAxis) {
    angles = {angles.x, angles.y, angle};
    axis.z = zAxis;
}
