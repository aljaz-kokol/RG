#include "AmbientLight.h"

AmbientLight::AmbientLight(const ShaderProgram& program, const Color &color, GLfloat intensity):
    Light(program),color(color), intensity(intensity) {}

void AmbientLight::use() const {
    program.setUniform("directionalLight.color", color.getRGB());
    program.setUniform("directionalLight.ambientIntensity", intensity);
}

void AmbientLight::unbind() const {
    program.setUniform("directionalLight.color", 0);
    program.setUniform("directionalLight.ambientIntensity", 0);
}

const Color &AmbientLight::getColor() const {
    return color;
}

GLfloat AmbientLight::getIntensity() const {
    return intensity;
}

void AmbientLight::setColor(const Color &color) {
    AmbientLight::color = color;
}

void AmbientLight::setIntensity(GLfloat intensity) {
    AmbientLight::intensity = intensity;
    if (intensity >= 1) {
        AmbientLight::intensity = 1;
    } else if (intensity <= 0) {
        AmbientLight::intensity = 0;
    }
}
