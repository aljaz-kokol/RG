#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_BUFFERLAYOUT_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_BUFFERLAYOUT_H

#include<vector>
#include<cstdint>
#include <GL/glew.h>

struct BufferElement  {
    uint32_t type;
    GLint count;
    uint32_t normalized;

    static uint32_t getSizeOfType(uint32_t type) {
        switch (type) {
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
            default: return 0;
        }
    }
};

class BufferLayout {
private:
    std::vector<BufferElement> elements;
    GLuint stride;
public:
    BufferLayout(): stride(0) {}
    template<uint32_t type> void push(GLint count);
    [[nodiscard]] GLuint getStride() const;
    [[nodiscard]] const std::vector<BufferElement>& getElements() const;
};

template<uint32_t type>
void BufferLayout::push(GLint count) {
    elements.push_back({ type, count, GL_FALSE });
    stride += count * BufferElement::getSizeOfType(type);
}

#endif