#include "AmbientLight.h"

AmbientLight::AmbientLight(const ShaderProgram& program, const Color &color, GLfloat intensity):
    Light(program),color(color), intensity(intensity) {}

void AmbientLight::use() const {
    program.setUniform("directionalLight.color", color.getRGB());
    program.setUniform("directionalLight.ambientIntensity", intensity);
}