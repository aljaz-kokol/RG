#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_CUBOIDSHAPE_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_CUBOIDSHAPE_H

#include <unordered_map>
#include <string>
#include "../Cuboid.h"
#include "cuboid-shape-element/CuboidShapeElement.h"
#include "../../../utils/DrawMode.h"
#include "../../../renderer/Renderer.h"

struct CuboidShapeElementDescriptor {
    glm::vec3 positions;
    Color color;
};

class CuboidShape {
private:
    const Cuboid& cuboid;
    std::vector<CuboidShapeElement> elements;
public:
    CuboidShape(const Cuboid& cuboid, const std::vector<CuboidShapeElementDescriptor>& elements, float scale = 1.0f);
    template<DrawMode mode>
    void draw() const;
    void move(Direction direction, float value, GLfloat delta = 1.0);
    void scale(Direction direction, float value, GLfloat delta = 1.0);
    void rotate(RotationDirection rotationDirection, float value, GLfloat delta = 1.0);
};

template<DrawMode mode>
void CuboidShape::draw() const {
    glm::vec3 center(0);
    for (const CuboidShapeElement& element : elements) {
        center += element.getTranslation().getValues();
    }
    center /= elements.size();
    for (const auto& element : elements) {
        cuboid.applyTransformations("model", element.getTransformationsWithCenter(center));
        cuboid.setColor(element.getColor());
        Renderer::draw<mode>(cuboid);
    }
}

#endif