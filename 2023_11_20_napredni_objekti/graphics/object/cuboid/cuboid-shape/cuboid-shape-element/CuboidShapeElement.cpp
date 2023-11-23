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

void CuboidShapeElement::scale(Direction direction, float increment, GLfloat delta) {
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

void CuboidShapeElement::move(Direction direction, float value, GLfloat delta) {
    const GLfloat VELOCITY = value * delta;
    if (direction == Direction::LEFT) {
        positions[0] -= value * VELOCITY;
    } else if (direction == Direction::RIGHT) {
        positions[0] += value * VELOCITY;
    } else if (direction == Direction::UP) {
        positions[1] += value * VELOCITY;
    } else if (direction == Direction::DOWN) {
        positions[1] -= value * VELOCITY;
    } else if (direction == Direction::FRONT) {
        positions[2] += value * VELOCITY;
    } else if (direction == Direction::BACK) {
        positions[2] -= value * VELOCITY;
    }

    translation.setValues(glm::vec3(
            2 * scaleTrans.getFactors()[0] * positions[0] * cuboid.getWidth(),
            2 * scaleTrans.getFactors()[1] * positions[1] * cuboid.getHeight(),
        2 * positions[2] * cuboid.getDepth()
    ));
}

void CuboidShapeElement::rotate(RotationDirection rotationDirection, float value, GLfloat delta) {
    const GLfloat VELOCITY = value * delta;
    int8_t rotationDirValue = static_cast<std::underlying_type<RotationDirection>::type>(rotationDirection) < 0 ? -1 : 1;
    if (rotationDirection == RotationDirection::X_POS || rotationDirection == RotationDirection::X_NEG) {
        rotation.setXAngle(rotation.getAngles().x + rotationDirValue * value*  VELOCITY);
    } else if (rotationDirection == RotationDirection::Y_POS || rotationDirection == RotationDirection::Y_NEG) {
        rotation.setYAngle(rotation.getAngles().y + rotationDirValue * value* VELOCITY);
    } else if (rotationDirection == RotationDirection::Z_POS || rotationDirection == RotationDirection::Z_NEG) {
        rotation.setZAngle(rotation.getAngles().z + rotationDirValue * value* VELOCITY);
    }
}

const Color &CuboidShapeElement::getColor() const {
    return color;
}

const Translation &CuboidShapeElement::getTranslation() const {
    return translation;
}
