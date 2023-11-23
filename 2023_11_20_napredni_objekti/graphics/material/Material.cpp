#include "Material.h"

Material::Material(const ShaderProgram &program): program(program), shininess(0), specularIntensity(0) {}

Material::Material(const ShaderProgram &program, GLfloat specularIntensity, GLfloat shininess)
: program(program), specularIntensity(specularIntensity), shininess(shininess) {}

void Material::bind() const {
    program.setUniform("material.specularIntensity", specularIntensity);
    program.setUniform("material.shininess", shininess);
}

void Material::unbind() const {
    program.setUniform("material.specularIntensity", 0.0f);
    program.setUniform("material.shininess", 0.0f);
}