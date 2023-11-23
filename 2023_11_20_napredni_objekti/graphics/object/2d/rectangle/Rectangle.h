#ifndef INC_2023_11_20_NAPREDNI_OBJEKTI_RECTANGLE_H
#define INC_2023_11_20_NAPREDNI_OBJEKTI_RECTANGLE_H

#include "../../Mesh.h"

class Rectangle : public Mesh {
private:
    GLfloat width;
    GLfloat height;
public:
    explicit Rectangle(const ShaderProgram& shader, GLfloat width = 1.0f, GLfloat height = 1.0f);
};

#endif