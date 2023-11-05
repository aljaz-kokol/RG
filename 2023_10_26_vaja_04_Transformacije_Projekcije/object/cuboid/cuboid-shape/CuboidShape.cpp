#include "CuboidShape.h"
#include "../../transformation/scale/Scale.h"
#include "../../transformation/translation/Translation.h"
#include "../../../renderer/Renderer.h"
#include <ranges>

CuboidShape::CuboidShape(const Cuboid &cuboid, const std::vector<CuboidShapeElementDescriptor>& elements, float scale): scaleFactor(scale), cuboid(cuboid) {
    for (const CuboidShapeElementDescriptor& element: elements) {
        this->elements.emplace_back(cuboid, element.positions, element.color, scale);
    }
}

void CuboidShape::draw() const {
    glm::vec3 center(0);
    for (const CuboidShapeElement& element : elements) {
        center += element.getTranslation().getValues();
    }
    center /= elements.size();
    for (const auto& element : elements) {
        cuboid.applyTransformations("model", element.getTransformationsWithCenter(center));
        cuboid.setColor(element.getColor());
        Renderer::draw(cuboid);
    }
}

void CuboidShape::move(Direction direction, float value, GLfloat delta) {
    for (CuboidShapeElement& element : elements) {
        element.move(direction, value, delta);
    }
}

void CuboidShape::rotate(Direction direction, float value, GLfloat delta) {
    for (CuboidShapeElement& element : elements) {
        element.rotate(direction, value, delta);
    }
}

void CuboidShape::scale(Direction direction, float value, GLfloat delta) {
    for (CuboidShapeElement& element : elements) {
        element.scale(direction, value, delta);
    }
}