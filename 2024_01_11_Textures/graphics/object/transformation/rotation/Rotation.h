#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_ROTATION_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_ROTATION_H

#include "../Transformation.h"

class Rotation : public Transformation {
private:
    glm::vec3 axis;
    glm::vec3 angles;
public:
    explicit Rotation(float angle, const glm::vec3 &factors = glm::vec3(1));
    explicit Rotation(const glm::vec3& angles, const glm::vec3 &factors = glm::vec3(1));
    [[nodiscard]] glm::mat4 transform() const override;
    [[nodiscard]] const glm::vec3 &getAxis() const;
    [[nodiscard]] const glm::vec3 &getAngles() const;

    void setAngles(const glm::vec3 &angles, const glm::vec3 &axis = glm::vec3(1));
    void setXAngle(float angle, float xAxis = 1.0);
    void setYAngle(float angle, float yAxis = 1.0);
    void setZAngle(float angle, float zAxis = 1.0);

    void setAxis(const glm::vec3 &axis);
};

#endif