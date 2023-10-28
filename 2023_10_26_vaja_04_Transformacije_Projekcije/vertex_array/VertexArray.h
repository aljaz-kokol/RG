#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_VERTEXARRAY_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_VERTEXARRAY_H

#include <GL/glew.h>
#include "../buffer/Buffer.h"
#include "../buffer/layout/BufferLayout.h"
#include "../buffer/vertex/VertexBuffer.h"

class VertexArray {
private:
    GLuint id;
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;
    void addBuffer(const VertexBuffer& buffer, const BufferLayout& layout);
};


#endif