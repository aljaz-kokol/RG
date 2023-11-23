#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_TRANSFORMATION_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_TRANSFORMATION_H

#include <glm/glm.hpp>

class Transformation {
public:
    Transformation() = default;
    virtual ~Transformation() = default;
    [[nodiscard]] virtual glm::mat4 transform() const = 0;
};

#endif