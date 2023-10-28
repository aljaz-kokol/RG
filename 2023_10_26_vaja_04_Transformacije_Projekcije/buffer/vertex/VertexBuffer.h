#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_VERTEXBUFFER_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_VERTEXBUFFER_H

#include "../Buffer.h"

class VertexBuffer : public Buffer<GLfloat> {
public:
    explicit VertexBuffer(const std::vector<GLfloat> &data);
};

#endif
