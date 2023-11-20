#ifndef INC_2023_10_12_VAJA_2_PIRAMIDA_CUBOID_H
#define INC_2023_10_12_VAJA_2_PIRAMIDA_CUBOID_H

#include "../Mesh.h"
#include <cstdint>

class Cuboid : public Mesh {
private:
    float width;
    float height;
    float depth;
public:
    Cuboid(const ShaderProgram& shader, float width, float height, float depth);
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight() const;
    [[nodiscard]] float getDepth() const;
};


#endif
