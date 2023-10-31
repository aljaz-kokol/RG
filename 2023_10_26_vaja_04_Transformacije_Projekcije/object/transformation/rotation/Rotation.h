#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_ROTATION_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_ROTATION_H

#include "../Transformation.h"

class Rotation : public Transformation {
private:
    glm::vec3 factors;
    float angle;
public:
    explicit Rotation(float angle, const glm::vec3 &factors);
    [[nodiscard]] glm::mat4 transform() const override;
};

#endif