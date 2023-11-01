#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_CUBOIDSHAPE_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_CUBOIDSHAPE_H

#include <unordered_map>
#include <string>
#include "../Cuboid.h"

struct CuboidShapeElement {
    Color color;
    std::vector<std::shared_ptr<Transformation>> transformations;
};

struct CuboidShapeElementDescriptor {
    std::string_view name;
    Color color;
    std::array<float, 3> positions;
};

class CuboidShape {
private:
    float scale;
    const Cuboid& cuboid;
    std::unordered_map<std::string_view , CuboidShapeElement> elements;
public:
    CuboidShape(const Cuboid& cuboid, const std::vector<CuboidShapeElementDescriptor>& elements, float scale = 1.0f);
    void draw() const;
};


#endif