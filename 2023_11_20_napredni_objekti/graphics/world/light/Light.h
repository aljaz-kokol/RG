#ifndef INC_03_TEXTURES_LIGHT_H
#define INC_03_TEXTURES_LIGHT_H

#include "../../color/Color.h"
#include "../../shader/program/ShaderProgram.h"
#include <glm/glm.hpp>
#include <GL/glew.h>

class Light {
private:
    const ShaderProgram& program;
    Color color;
    GLfloat ambientIntensity;

    glm::vec3 direction;
    GLfloat diffuseIntensity;
public:
    Light(const ShaderProgram& program);
    explicit Light(const ShaderProgram& program, const Color& color, GLfloat ambientIntensity, const glm::vec3& direction, GLfloat diffuseIntensity);
    void use() const;
};

#endif