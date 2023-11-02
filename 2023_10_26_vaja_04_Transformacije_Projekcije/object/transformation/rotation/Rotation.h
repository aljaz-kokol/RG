#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_ROTATION_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_ROTATION_H

#include "../Transformation.h"

class Rotation : public Transformation {
private:
    glm::vec3 axis;
    float angle;
public:
    explicit Rotation(float angle, const glm::vec3 &factors);
    [[nodiscard]] glm::mat4 transform() const override;
    [[nodiscard]] const glm::vec3 &getAxis() const;
    [[nodiscard]] float getAngle() const;

    void setAxis(const glm::vec3 &axis);
    void setAngle(float angle);
};

#endif