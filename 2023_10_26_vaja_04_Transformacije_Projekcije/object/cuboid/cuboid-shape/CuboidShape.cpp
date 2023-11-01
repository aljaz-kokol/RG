#include "CuboidShape.h"
#include "../../transformation/scale/Scale.h"
#include "../../transformation/translation/Translation.h"
#include "../../../renderer/Renderer.h"
#include <ranges>

CuboidShape::CuboidShape(const Cuboid &cuboid, const std::vector<CuboidShapeElementDescriptor>& elements, float scale): scale(scale), cuboid(cuboid) {
    for (const CuboidShapeElementDescriptor& element: elements) {
        this->elements[element.name] = { element.color, {
            std::make_shared<Translation>(
                glm::vec3(
                    2 * scale * element.positions[0] * cuboid.getWidth(),
                    2 * scale * element.positions[1] * cuboid.getHeight(),
                    2 * element.positions[2] * cuboid.getDepth()
                )
            ),
            std::make_shared<Scale>(scale),
        } };
    }
}

void CuboidShape::draw() const {
    for (const auto& element : elements) {
        cuboid.applyTransformations("model", element.second.transformations);
        cuboid.setColor(element.second.color);
        Renderer::draw(cuboid);
    }
}
