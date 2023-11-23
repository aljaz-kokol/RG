#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const std::vector<GLuint> &indices): Buffer<GLuint>(GL_ELEMENT_ARRAY_BUFFER, indices), count(indices.size()) {}

GLuint IndexBuffer::getCount() const {
    return count;
}