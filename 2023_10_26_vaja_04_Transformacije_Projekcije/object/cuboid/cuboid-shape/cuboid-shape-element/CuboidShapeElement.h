#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_CUBOIDSHAPEELEMENT_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_CUBOIDSHAPEELEMENT_H

#include <string>
#include "../../../../color/Color.h"
#include "../../../transformation/translation/Translation.h"
#include "../../../transformation/scale/Scale.h"
#include "../../../transformation/rotation/Rotation.h"
#include "../../Cuboid.h"
#include "../../../../utils/Direction.h"
#include "../../../../utils/RotationDirection.h"

class CuboidShapeElement {
private:
    const Cuboid& cuboid;
    Color color;
    glm::vec3 positions;
    Translation translation;
    Scale scaleTrans;
    Rotation rotation;
public:
    CuboidShapeElement(const Cuboid& cuboid, const glm::vec3& positions, const Color& color, float scaleFactor = 1.0f);

    [[nodiscard]] const Color& getColor() const;
    [[nodiscard]] std::vector<std::shared_ptr<Transformation>> getTransformations() const;
    [[nodiscard]] std::vector<std::shared_ptr<Transformation>> getTransformationsWithCenter(const glm::vec3& center) const;
    [[nodiscard]] const Translation &getTranslation() const;


    void scale(Direction direction, float increment, GLfloat delta = 1.0);
    void move(Direction direction, float value, GLfloat delta = 1.0);
    void rotate(RotationDirection rotationDirection, float value, GLfloat delta = 1.0);
};

#endif