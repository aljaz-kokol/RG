#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_COLOR_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_COLOR_H

#include <glm/glm.hpp>

class Color {
private:
    glm::vec4 values;
public:
    static const constexpr glm::vec4 RED = { 1, 0, 0, 1 };
    static const constexpr glm::vec4 GREEN = { 0, 1, 0, 1 };
    static const constexpr glm::vec4 BLUE = { 0, 0, 1, 1 };
    static const constexpr glm::vec4 YELLOW = { 1, 1, 0, 1 };
    static const constexpr glm::vec4 CYAN = { 0, 1, 1, 1 };
    static const constexpr glm::vec4 MAGENTA = { 1, 0, 1, 1 };
    static const constexpr glm::vec4 WHITE = { 1, 1, 1, 1 };
    static const constexpr glm::vec4 BLACK = { 0, 0, 0, 1 };

    Color(const glm::vec4& values = BLACK);
    Color(const glm::vec3& values = glm::vec3(0, 0, 0));
    [[nodiscard]] const glm::vec4& getRGBA() const;
    [[nodiscard]] glm::vec3 getRGB() const;

    [[nodiscard]] float getR() const;
    [[nodiscard]] float getG() const;
    [[nodiscard]] float getB() const;
    [[nodiscard]] float getA() const;

    [[nodiscard]] Color operator+(const Color& color) const;
    [[nodiscard]] Color operator-(const Color& color) const;

    [[nodiscard]] Color operator+(const glm::vec4& color) const;
    [[nodiscard]] Color operator-(const glm::vec4& color) const;
};


#endif