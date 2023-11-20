#include "Material.h"

Material::Material(const ShaderProgram &program): program(program), shininess(0), specularIntensity(0) {}

Material::Material(const ShaderProgram &program, GLfloat specularIntensity, GLfloat shininess)
: program(program), specularIntensity(specularIntensity), shininess(shininess) {}

void Material::use() const {
    program.setUniform("material.specularIntensity", specularIntensity);
    program.setUniform("material.shininess", shininess);
}