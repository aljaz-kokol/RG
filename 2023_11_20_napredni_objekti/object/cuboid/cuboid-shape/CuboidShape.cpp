#include "CuboidShape.h"
#include "../../transformation/scale/Scale.h"
#include "../../transformation/translation/Translation.h"
#include "../../../renderer/Renderer.h"
#include <ranges>

CuboidShape::CuboidShape(const Cuboid &cuboid, const std::vector<CuboidShapeElementDescriptor>& elements, float scale): cuboid(cuboid) {
    for (const CuboidShapeElementDescriptor& element: elements) {
        this->elements.emplace_back(cuboid, element.positions, element.color, scale);
    }
}

void CuboidShape::move(Direction direction, float value, GLfloat delta) {
    for (CuboidShapeElement& element : elements) {
        element.move(direction, value, delta);
    }
}

void CuboidShape::rotate(RotationDirection rotationDirection, float value, GLfloat delta) {
    for (CuboidShapeElement& element : elements) {
        element.rotate(rotationDirection, value, delta);
    }
}

void CuboidShape::scale(Direction direction, float value, GLfloat delta) {
    for (CuboidShapeElement& element : elements) {
        element.scale(direction, value, delta);
    }
}