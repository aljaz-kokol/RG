#include "Light.h"

Light::Light(const ShaderProgram& program): Light(program, glm::vec3 (1.0f, 1.0f, 1.0f), 1.0f, glm::vec3(0, -1, 0), 1.0f) {}

Light::Light(const ShaderProgram& program, const Color& color, GLfloat ambientIntensity, const glm::vec3& direction, GLfloat diffuseIntensity)
: program(program), color(color), ambientIntensity(ambientIntensity), direction(direction), diffuseIntensity(diffuseIntensity) {}

void Light::use() const {
    program.setUniform("directionalLight.color", color.getRGB());
    program.setUniform("directionalLight.ambientIntensity", ambientIntensity);

    program.setUniform("directionalLight.direction", direction);
    program.setUniform("directionalLight.diffuseIntensity", diffuseIntensity);
}