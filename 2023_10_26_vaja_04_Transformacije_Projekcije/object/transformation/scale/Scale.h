#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_SCALE_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_SCALE_H

#include "../Transformation.h"

class Scale : public Transformation {
private:
    glm::vec3 factors;
public:
    explicit Scale(const glm::vec3& factors);
    explicit Scale(float factor);
    [[nodiscard]] glm::mat4 transform() const override;
};


#endif