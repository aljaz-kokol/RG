#ifndef INC_03_TEXTURES_MATERIAL_H
#define INC_03_TEXTURES_MATERIAL_H

#include <GL/glew.h>
#include "../shader/program/ShaderProgram.h"

class Material {
private:
    const ShaderProgram& program;
    GLfloat specularIntensity;
    GLfloat shininess;
public:
    Material(const ShaderProgram& program);
    Material(const ShaderProgram& program, GLfloat specularIntensity, GLfloat shininess);

    void bind() const;
    void unbind() const;
};

#endif