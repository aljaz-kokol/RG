#include "VertexArray.h"
#include "../renderer/Renderer.h"

VertexArray::VertexArray(): id(0) {
    glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
    if (id != 0) {
        glDeleteVertexArrays(1, &id);
    }
}

void VertexArray::bind() const {
    glBindVertexArray(id);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}


void VertexArray::addBuffer(const VertexBuffer &buffer, const BufferLayout &layout) {
    bind();
    buffer.bind();
    const std::vector<BufferElement>& elements = layout.getElements();
    uint32_t offset = 0;
    for (size_t i = 0; i < elements.size(); i++) {
        const BufferElement& element = elements.at(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        glEnableVertexAttribArray(i);
        offset += element.count * BufferElement::getSizeOfType(element.type);
    }
}