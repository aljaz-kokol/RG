#include "BufferLayout.h"

GLuint BufferLayout::getStride() const {
    return stride;
}

const std::vector<BufferElement> &BufferLayout::getElements() const {
    return elements;
}
