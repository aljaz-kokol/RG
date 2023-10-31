#include "Color.h"

Color::Color(const glm::vec4 &values): values(values) {}

const glm::vec4 &Color::getValues() const {
    return values;
}

Color Color::operator+(const Color &color) const {
    return Color(values + color.getValues());
}

Color Color::operator-(const Color &color) const {
    return Color(values - color.getValues());
}

Color Color::operator+(const glm::vec4& color) const {
    return Color(values + color);
}

Color Color::operator-(const glm::vec4& color) const {
    return Color(values - color);
}