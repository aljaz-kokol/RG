#ifndef INC_2023_12_20_SHADEING_AMBIENTLIGHT_H
#define INC_2023_12_20_SHADEING_AMBIENTLIGHT_H

#include "../../../color/Color.h"
#include "../Light.h"
#include <GL/glew.h>

class AmbientLight : public Light {
private:
    Color color;
    GLfloat intensity;
public:
    AmbientLight(const ShaderProgram& program, const Color& color, GLfloat intensity);
    void use() const override;
    void unbind() const;

    const Color &getColor() const;

    GLfloat getIntensity() const;

    void setColor(const Color &color);

    void setIntensity(GLfloat intensity);
};

#endif