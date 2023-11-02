#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_CUBOIDSHAPE_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_CUBOIDSHAPE_H

#include <unordered_map>
#include <string>
#include "../Cuboid.h"
#include "cuboid-shape-element/CuboidShapeElement.h"

struct CuboidShapeElementDescriptor {
    glm::vec3 positions;
    Color color;
};

class CuboidShape {
private:
    float scaleFactor;
    const Cuboid& cuboid;
    std::vector<CuboidShapeElement> elements;
public:
    CuboidShape(const Cuboid& cuboid, const std::vector<CuboidShapeElementDescriptor>& elements, float scale = 1.0f);
    void draw() const;
    void move(Direction direction, float value);
    void scale(Direction direction, float value);
    void rotate(Direction direction, float value);

};


#endif