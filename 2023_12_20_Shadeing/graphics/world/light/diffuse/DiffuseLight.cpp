#include "DiffuseLight.h"

DiffuseLight::DiffuseLight(const ShaderProgram &program, const glm::vec3 &direction, GLfloat intensity)
: Light(program), direction(direction), intensity(intensity) {}

void DiffuseLight::use() const {
    program.setUniform("directionalLight.direction", direction);
    program.setUniform("directionalLight.diffuseIntensity", intensity);
}