#include "Color.h"

Color::Color(const glm::vec4 &values): values(values) {}
Color::Color(const glm::vec3 &values): values(values, 1.0) {}

const glm::vec4 &Color::getRGBA() const {
    return values;
}

glm::vec3 Color::getRGB() const {
    return { values };
}

float Color::getR() const {
    return values.x;
}

float Color::getG() const {
    return values.y;
}

float Color::getB() const {
    return values.z;
}

float Color::getA() const {
    return values.w;
}

Color Color::operator+(const Color &color) const {
    return Color(values + color.getRGBA());
}

Color Color::operator-(const Color &color) const {
    return Color(values - color.getRGBA());
}

Color Color::operator+(const glm::vec4& color) const {
    return Color(values + color);
}

Color Color::operator-(const glm::vec4& color) const {
    return Color(values - color);
}