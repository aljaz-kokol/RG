#ifndef INC_2023_12_20_SHADEING_DIFFUSELIGHT_H
#define INC_2023_12_20_SHADEING_DIFFUSELIGHT_H


#include "../Light.h"

class DiffuseLight : public Light {
private:
    glm::vec3 direction;
    GLfloat intensity;
public:
    DiffuseLight(const ShaderProgram& program, const glm::vec3& direction, GLfloat intensity);
    void use() const override;
};


#endif //INC_2023_12_20_SHADEING_DIFFUSELIGHT_H
