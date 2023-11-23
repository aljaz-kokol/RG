#include "Rectangle.h"

Rectangle::Rectangle(const ShaderProgram& shader, GLfloat width, GLfloat height)
        : width(width), height(height), Mesh(
        shader,
        {
                -width, -height, 0.0f, // 0
                width, -height, 0.0f, // 1
                -width, height, 0.0f, // 2
                width, height, 0.0f, // 3
        },
        {
                0, 1, 2,
                1, 2, 3
        }
) {}