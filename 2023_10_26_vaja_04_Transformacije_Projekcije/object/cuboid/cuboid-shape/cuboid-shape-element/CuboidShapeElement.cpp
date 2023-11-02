#include "CuboidShapeElement.h"

CuboidShapeElement::CuboidShapeElement(const Cuboid& cuboid, const glm::vec3& positions, const Color &color, float scaleFactor)
: cuboid(cuboid), positions(positions), color(color), scaleTrans(scaleFactor), rotation(0, glm::vec3(1)),
  translation(glm::vec3(
      2 * scaleFactor * positions[0] * cuboid.getWidth(),
      2 * scaleFactor * positions[1] * cuboid.getHeight(),
      2 * positions[2] * cuboid.getDepth()
  )) {}

std::vector<std::shared_ptr<Transformation>> CuboidShapeElement::getTransformations() const {
    return std::vector<std::shared_ptr<Transformation>>({
        std::make_shared<Translation>(translation),
        std::make_shared<Rotation>(rotation),
        std::make_shared<Scale>(scaleTrans),
    });
}

std::vector<std::shared_ptr<Transformation>> CuboidShapeElement::getTransformationsWithCenter(const glm::vec3 &center) const {
    return std::vector<std::shared_ptr<Transformation>>({
        std::make_shared<Translation>(center),
        std::make_shared<Rotation>(rotation),
        std::make_shared<Translation>(translation.getValues() - center),
        std::make_shared<Scale>(scaleTrans),
    });
}



void CuboidShapeElement::scale(Direction direction, float increment) {
    if (direction == Direction::UP) {
        scaleTrans.setFactors(scaleTrans.getFactors() + increment);
    } else {
        scaleTrans.setFactors(scaleTrans.getFactors() - increment);
    }
    translation.setValues(glm::vec3(
            2 * scaleTrans.getFactors()[0] * positions[0] * cuboid.getWidth(),
            2 * scaleTrans.getFactors()[1] * positions[1] * cuboid.getHeight(),
        2 * positions[2] * cuboid.getDepth()
    ));
}

void CuboidShapeElement::move(Direction direction, float value) {
    if (direction == Direction::LEFT) {
        positions[0] -= value;
    } else if (direction == Direction::RIGHT) {
        positions[0] += value;
    } else if (direction == Direction::UP) {
        positions[1] += value;
    } else if (direction == Direction::DOWN) {
        positions[1] -= value;
    }

    translation.setValues(glm::vec3(
            2 * scaleTrans.getFactors()[0] * positions[0] * cuboid.getWidth(),
            2 * scaleTrans.getFactors()[1] * positions[1] * cuboid.getHeight(),
        2 * positions[2] * cuboid.getDepth()
    ));
}

void CuboidShapeElement::rotate(Direction direction, float value) {
    if (direction == Direction::RIGHT) {
        rotation.setAngle(rotation.getAngle() + value);
        rotation.setAxis({ 0, 1, 0 });
    }
}

const Color &CuboidShapeElement::getColor() const {
    return color;
}

const glm::vec3 &CuboidShapeElement::getPositions() const {
    return positions;
}
