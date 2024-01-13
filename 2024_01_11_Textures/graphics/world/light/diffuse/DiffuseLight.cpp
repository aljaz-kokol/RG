#include "DiffuseLight.h"

DiffuseLight::DiffuseLight(const ShaderProgram &program, const glm::vec3 &direction, GLfloat intensity)
: Light(program), position(direction), intensity(intensity) {}

void DiffuseLight::use() const {
    program.setUniform("directionalLight.position", position);
    program.setUniform("directionalLight.diffuseIntensity", intensity);
}

const glm::vec3 &DiffuseLight::getDirection() const {
    return position;
}

GLfloat DiffuseLight::getIntensity() const {
    return intensity;
}

void DiffuseLight::setDirection(const glm::vec3 &direction) {
    DiffuseLight::position = direction;
}

void DiffuseLight::setIntensity(GLfloat intensity) {
    DiffuseLight::intensity = intensity;
    if (intensity >= 1) {
        DiffuseLight::intensity = 1;
    } else if (intensity <= 0) {
        DiffuseLight::intensity = 0;
    }
}
