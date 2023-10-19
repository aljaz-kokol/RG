#include "Cuboid.h"

Cuboid::Cuboid(const ShaderProgram& shader, float width, float height, float depth)
: Mesh(shader, {
               -width, -height,  depth,
               width, -height,  depth,
               width,  height,  depth,
               -width,  height,  depth,
               // back
               -width, -height, -depth,
               width, -height, -depth,
               width,  height, -depth,
               -width,  height, -depth
    }, {
        // front
        0, 1, 2,
        2, 3, 0,
        // right
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // left
        4, 0, 3,
        3, 7, 4,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // top
        3, 2, 6,
        6, 7, 3

}) {}