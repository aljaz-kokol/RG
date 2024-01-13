#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const std::vector<GLfloat> &data) : Buffer(GL_ARRAY_BUFFER, data) {}
