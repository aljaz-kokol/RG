#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_ROTATION_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_ROTATION_H

#include "../Transformation.h"

class Rotation : public Transformation {
private:
    glm::vec3 axis;
    glm::vec3 angles;
public:
    explicit Rotation(float angle, const glm::vec3 &factors);
    [[nodiscard]] glm::mat4 transform() const override;
    [[nodiscard]] const glm::vec3 &getAxis() const;
    [[nodiscard]] const glm::vec3 &getAngles() const;

    void setAngles(const glm::vec3 &angles);
    void setXAngle(float angle);
    void setYAngle(float angle);
    void setZAngle(float angle);

    void setAxis(const glm::vec3 &axis);
};

#endif