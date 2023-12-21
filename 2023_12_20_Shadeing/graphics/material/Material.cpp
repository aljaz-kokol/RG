#include "Material.h"

Material::Material(const ShaderProgram &program): program(program), shininess(0), specularIntensity(0) {}

Material::Material(const ShaderProgram &program, GLfloat specularIntensity, GLfloat shininess)
: program(program), specularIntensity(specularIntensity), shininess(shininess) {}

void Material::use() const {
    program.setUniform("material.specularIntensity", specularIntensity);
    program.setUniform("material.shininess", shininess);
}

GLfloat Material::getSpecularIntensity() const {
    return specularIntensity;
}

GLfloat Material::getShininess() const {
    return shininess;
}

void Material::setSpecularIntensity(GLfloat specularIntensity) {
    Material::specularIntensity = specularIntensity;
    if (specularIntensity >= 1) {
        Material::specularIntensity = 1;
    } else if (specularIntensity <= 0) {
        Material::specularIntensity = 0;
    }
}

void Material::setShininess(GLfloat shininess) {
    Material::shininess = shininess;
    if (shininess >= 1000) {
        Material::shininess = 1000;
    } else if (shininess <= 1) {
        Material::shininess = 1;
    }
}
