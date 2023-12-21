#ifndef INC_03_TEXTURES_LIGHT_H
#define INC_03_TEXTURES_LIGHT_H

#include "../../color/Color.h"
#include "../../shader/program/ShaderProgram.h"
#include <glm/glm.hpp>
#include <GL/glew.h>

class Light {
protected:
    const ShaderProgram& program;

public:
    Light(const ShaderProgram& program);
    virtual ~Light() = default;
    virtual void use() const = 0;
};

#endif