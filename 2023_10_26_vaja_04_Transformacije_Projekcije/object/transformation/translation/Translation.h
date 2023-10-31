#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_TRANSLATION_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_TRANSLATION_H

#include "../Transformation.h"

class Translation: public Transformation {
private:
    glm::vec3 values;
public:
    explicit Translation(const glm::vec3& values);
   [[nodiscard]] glm::mat4 transform() const override;
};

#endif